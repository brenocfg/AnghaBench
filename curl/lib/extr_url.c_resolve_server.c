#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timediff_t ;
struct hostname {char const* dispname; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {struct hostname host; } ;
struct TYPE_5__ {struct hostname host; } ;
struct TYPE_4__ {scalar_t__ socksproxy; scalar_t__ conn_to_port; scalar_t__ conn_to_host; int /*<<< orphan*/  proxy; scalar_t__ reuse; } ;
struct connectdata {char* unix_domain_socket; struct Curl_dns_entry* dns_entry; scalar_t__ port; void* hostname_resolve; TYPE_3__ http_proxy; TYPE_2__ socks_proxy; TYPE_1__ bits; scalar_t__ remote_port; scalar_t__ conn_to_port; struct hostname host; struct hostname conn_to_host; int /*<<< orphan*/  abstract_unix_socket; } ;
struct Curl_easy {char* unix_domain_socket; struct Curl_dns_entry* dns_entry; scalar_t__ port; void* hostname_resolve; TYPE_3__ http_proxy; TYPE_2__ socks_proxy; TYPE_1__ bits; scalar_t__ remote_port; scalar_t__ conn_to_port; struct hostname host; struct hostname conn_to_host; int /*<<< orphan*/  abstract_unix_socket; } ;
struct Curl_dns_entry {int /*<<< orphan*/  inuse; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_HOST ; 
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_PROXY ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OPERATION_TIMEDOUT ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int CURLRESOLV_PENDING ; 
 int CURLRESOLV_TIMEDOUT ; 
 int Curl_resolv_timeout (struct connectdata*,void*,int,struct Curl_dns_entry**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_timeleft (struct connectdata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Curl_unix2addr (char const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGASSERT (struct connectdata*) ; 
 int FALSE ; 
 int TRUE ; 
 struct Curl_dns_entry* calloc (int,int) ; 
 int /*<<< orphan*/  failf (struct connectdata*,char*,char const*) ; 
 int /*<<< orphan*/  free (struct Curl_dns_entry*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode resolve_server(struct Curl_easy *data,
                               struct connectdata *conn,
                               bool *async)
{
  CURLcode result = CURLE_OK;
  timediff_t timeout_ms = Curl_timeleft(data, NULL, TRUE);

  DEBUGASSERT(conn);
  DEBUGASSERT(data);
  /*************************************************************
   * Resolve the name of the server or proxy
   *************************************************************/
  if(conn->bits.reuse)
    /* We're reusing the connection - no need to resolve anything, and
       idnconvert_hostname() was called already in create_conn() for the re-use
       case. */
    *async = FALSE;

  else {
    /* this is a fresh connect */
    int rc;
    struct Curl_dns_entry *hostaddr;

#ifdef USE_UNIX_SOCKETS
    if(conn->unix_domain_socket) {
      /* Unix domain sockets are local. The host gets ignored, just use the
       * specified domain socket address. Do not cache "DNS entries". There is
       * no DNS involved and we already have the filesystem path available */
      const char *path = conn->unix_domain_socket;

      hostaddr = calloc(1, sizeof(struct Curl_dns_entry));
      if(!hostaddr)
        result = CURLE_OUT_OF_MEMORY;
      else {
        bool longpath = FALSE;
        hostaddr->addr = Curl_unix2addr(path, &longpath,
                                        conn->abstract_unix_socket);
        if(hostaddr->addr)
          hostaddr->inuse++;
        else {
          /* Long paths are not supported for now */
          if(longpath) {
            failf(data, "Unix socket path too long: '%s'", path);
            result = CURLE_COULDNT_RESOLVE_HOST;
          }
          else
            result = CURLE_OUT_OF_MEMORY;
          free(hostaddr);
          hostaddr = NULL;
        }
      }
    }
    else
#endif
    if(!conn->bits.proxy) {
      struct hostname *connhost;
      if(conn->bits.conn_to_host)
        connhost = &conn->conn_to_host;
      else
        connhost = &conn->host;

      /* If not connecting via a proxy, extract the port from the URL, if it is
       * there, thus overriding any defaults that might have been set above. */
      if(conn->bits.conn_to_port)
        conn->port = conn->conn_to_port;
      else
        conn->port = conn->remote_port;

      /* Resolve target host right on */
      conn->hostname_resolve = strdup(connhost->name);
      if(!conn->hostname_resolve)
        return CURLE_OUT_OF_MEMORY;
      rc = Curl_resolv_timeout(conn, conn->hostname_resolve, (int)conn->port,
                               &hostaddr, timeout_ms);
      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve host '%s'", connhost->dispname);
        result =  CURLE_COULDNT_RESOLVE_HOST;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
    else {
      /* This is a proxy that hasn't been resolved yet. */

      struct hostname * const host = conn->bits.socksproxy ?
        &conn->socks_proxy.host : &conn->http_proxy.host;

      /* resolve proxy */
      conn->hostname_resolve = strdup(host->name);
      if(!conn->hostname_resolve)
        return CURLE_OUT_OF_MEMORY;
      rc = Curl_resolv_timeout(conn, conn->hostname_resolve, (int)conn->port,
                               &hostaddr, timeout_ms);

      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve proxy '%s'", host->dispname);
        result = CURLE_COULDNT_RESOLVE_PROXY;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
    DEBUGASSERT(conn->dns_entry == NULL);
    conn->dns_entry = hostaddr;
  }

  return result;
}