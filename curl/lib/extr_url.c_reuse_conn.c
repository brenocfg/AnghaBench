#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * rawalloc; } ;
struct TYPE_7__ {int /*<<< orphan*/ * passwd; int /*<<< orphan*/ * user; TYPE_4__ host; } ;
struct TYPE_6__ {int /*<<< orphan*/ * passwd; int /*<<< orphan*/ * user; TYPE_4__ host; } ;
struct TYPE_5__ {int /*<<< orphan*/  reuse; scalar_t__ proxy_user_passwd; scalar_t__ user_passwd; } ;
struct connectdata {int /*<<< orphan*/ * unix_domain_socket; int /*<<< orphan*/  easyq; int /*<<< orphan*/ * localdev; TYPE_3__ socks_proxy; TYPE_2__ http_proxy; int /*<<< orphan*/ * options; int /*<<< orphan*/ * passwd; int /*<<< orphan*/ * user; TYPE_1__ bits; int /*<<< orphan*/ * hostname_resolve; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  conn_to_port; TYPE_4__ conn_to_host; TYPE_4__ host; int /*<<< orphan*/  data; int /*<<< orphan*/  proxy_ssl_config; int /*<<< orphan*/  ssl_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_free_primary_ssl_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_persistconninfo (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  conn_reset_all_postponed_data (struct connectdata*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_idnconverted_hostname (TYPE_4__*) ; 

__attribute__((used)) static void reuse_conn(struct connectdata *old_conn,
                       struct connectdata *conn)
{
  free_idnconverted_hostname(&old_conn->http_proxy.host);
  free_idnconverted_hostname(&old_conn->socks_proxy.host);

  free(old_conn->http_proxy.host.rawalloc);
  free(old_conn->socks_proxy.host.rawalloc);

  /* free the SSL config struct from this connection struct as this was
     allocated in vain and is targeted for destruction */
  Curl_free_primary_ssl_config(&old_conn->ssl_config);
  Curl_free_primary_ssl_config(&old_conn->proxy_ssl_config);

  conn->data = old_conn->data;

  /* get the user+password information from the old_conn struct since it may
   * be new for this request even when we re-use an existing connection */
  conn->bits.user_passwd = old_conn->bits.user_passwd;
  if(conn->bits.user_passwd) {
    /* use the new user name and password though */
    Curl_safefree(conn->user);
    Curl_safefree(conn->passwd);
    conn->user = old_conn->user;
    conn->passwd = old_conn->passwd;
    old_conn->user = NULL;
    old_conn->passwd = NULL;
  }

  conn->bits.proxy_user_passwd = old_conn->bits.proxy_user_passwd;
  if(conn->bits.proxy_user_passwd) {
    /* use the new proxy user name and proxy password though */
    Curl_safefree(conn->http_proxy.user);
    Curl_safefree(conn->socks_proxy.user);
    Curl_safefree(conn->http_proxy.passwd);
    Curl_safefree(conn->socks_proxy.passwd);
    conn->http_proxy.user = old_conn->http_proxy.user;
    conn->socks_proxy.user = old_conn->socks_proxy.user;
    conn->http_proxy.passwd = old_conn->http_proxy.passwd;
    conn->socks_proxy.passwd = old_conn->socks_proxy.passwd;
    old_conn->http_proxy.user = NULL;
    old_conn->socks_proxy.user = NULL;
    old_conn->http_proxy.passwd = NULL;
    old_conn->socks_proxy.passwd = NULL;
  }

  /* host can change, when doing keepalive with a proxy or if the case is
     different this time etc */
  free_idnconverted_hostname(&conn->host);
  free_idnconverted_hostname(&conn->conn_to_host);
  Curl_safefree(conn->host.rawalloc);
  Curl_safefree(conn->conn_to_host.rawalloc);
  conn->host = old_conn->host;
  conn->conn_to_host = old_conn->conn_to_host;
  conn->conn_to_port = old_conn->conn_to_port;
  conn->remote_port = old_conn->remote_port;
  Curl_safefree(conn->hostname_resolve);

  conn->hostname_resolve = old_conn->hostname_resolve;
  old_conn->hostname_resolve = NULL;

  /* persist connection info in session handle */
  Curl_persistconninfo(conn);

  conn_reset_all_postponed_data(old_conn); /* free buffers */

  /* re-use init */
  conn->bits.reuse = TRUE; /* yes, we're re-using here */

  Curl_safefree(old_conn->user);
  Curl_safefree(old_conn->passwd);
  Curl_safefree(old_conn->options);
  Curl_safefree(old_conn->http_proxy.user);
  Curl_safefree(old_conn->socks_proxy.user);
  Curl_safefree(old_conn->http_proxy.passwd);
  Curl_safefree(old_conn->socks_proxy.passwd);
  Curl_safefree(old_conn->localdev);
  Curl_llist_destroy(&old_conn->easyq, NULL);

#ifdef USE_UNIX_SOCKETS
  Curl_safefree(old_conn->unix_domain_socket);
#endif
}