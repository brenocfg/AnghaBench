#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {struct curl_slist* next; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {void* conn_to_port; void* conn_to_host; } ;
struct TYPE_3__ {char* rawalloc; char* name; } ;
struct connectdata {int conn_to_port; TYPE_2__ bits; TYPE_1__ conn_to_host; } ;
struct Curl_easy {int dummy; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 scalar_t__ parse_connect_to_string (struct Curl_easy*,struct connectdata*,int /*<<< orphan*/ ,char**,int*) ; 

__attribute__((used)) static CURLcode parse_connect_to_slist(struct Curl_easy *data,
                                       struct connectdata *conn,
                                       struct curl_slist *conn_to_host)
{
  CURLcode result = CURLE_OK;
  char *host = NULL;
  int port = -1;

  while(conn_to_host && !host && port == -1) {
    result = parse_connect_to_string(data, conn, conn_to_host->data,
                                     &host, &port);
    if(result)
      return result;

    if(host && *host) {
      conn->conn_to_host.rawalloc = host;
      conn->conn_to_host.name = host;
      conn->bits.conn_to_host = TRUE;

      infof(data, "Connecting to hostname: %s\n", host);
    }
    else {
      /* no "connect to host" */
      conn->bits.conn_to_host = FALSE;
      Curl_safefree(host);
    }

    if(port >= 0) {
      conn->conn_to_port = port;
      conn->bits.conn_to_port = TRUE;
      infof(data, "Connecting to port: %d\n", port);
    }
    else {
      /* no "connect to port" */
      conn->bits.conn_to_port = FALSE;
      port = -1;
    }

    conn_to_host = conn_to_host->next;
  }

#ifdef USE_ALTSVC
  if(data->asi && !host && (port == -1) &&
     (conn->handler->protocol == CURLPROTO_HTTPS)) {
    /* no connect_to match, try alt-svc! */
    const char *nhost;
    int nport;
    enum alpnid nalpnid;
    bool hit;
    host = conn->host.rawalloc;
    hit = Curl_altsvc_lookup(data->asi,
                             ALPN_h1, host, conn->remote_port, /* from */
                             &nalpnid, &nhost, &nport /* to */);
    if(hit) {
      char *hostd = strdup((char *)nhost);
      if(!hostd)
        return CURLE_OUT_OF_MEMORY;
      conn->conn_to_host.rawalloc = hostd;
      conn->conn_to_host.name = hostd;
      conn->bits.conn_to_host = TRUE;
      conn->conn_to_port = nport;
      conn->bits.conn_to_port = TRUE;
      infof(data, "Alt-svc connecting from [%s]%s:%d to [%s]%s:%d\n",
            Curl_alpnid2str(ALPN_h1), host, conn->remote_port,
            Curl_alpnid2str(nalpnid), hostd, nport);
    }
  }
#endif

  return result;
}