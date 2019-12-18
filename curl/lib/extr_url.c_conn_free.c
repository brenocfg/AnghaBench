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
struct TYPE_8__ {int /*<<< orphan*/  rawalloc; } ;
struct TYPE_7__ {TYPE_4__ host; int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; } ;
struct TYPE_6__ {TYPE_4__ host; int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; } ;
struct TYPE_5__ {int /*<<< orphan*/  rtsp_transport; int /*<<< orphan*/  cookiehost; int /*<<< orphan*/  host; int /*<<< orphan*/  ref; int /*<<< orphan*/  rangeline; int /*<<< orphan*/  te; int /*<<< orphan*/  accept_encoding; int /*<<< orphan*/  userpwd; int /*<<< orphan*/  uagent; int /*<<< orphan*/  proxyuserpwd; } ;
struct connectdata {int /*<<< orphan*/  ssl_extra; int /*<<< orphan*/  unix_domain_socket; int /*<<< orphan*/  proxy_ssl_config; int /*<<< orphan*/  ssl_config; int /*<<< orphan*/  localdev; int /*<<< orphan*/  easyq; int /*<<< orphan*/  connect_state; TYPE_3__ socks_proxy; TYPE_2__ http_proxy; int /*<<< orphan*/  secondaryhostname; int /*<<< orphan*/  hostname_resolve; TYPE_4__ conn_to_host; TYPE_4__ host; int /*<<< orphan*/  trailer; TYPE_1__ allocptr; int /*<<< orphan*/  options; int /*<<< orphan*/  sasl_authzid; int /*<<< orphan*/  oauth_bearer; int /*<<< orphan*/  passwd; int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_free_primary_ssl_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_reset_all_postponed_data (struct connectdata*) ; 
 int /*<<< orphan*/  free (struct connectdata*) ; 
 int /*<<< orphan*/  free_idnconverted_hostname (TYPE_4__*) ; 

__attribute__((used)) static void conn_free(struct connectdata *conn)
{
  if(!conn)
    return;

  free_idnconverted_hostname(&conn->host);
  free_idnconverted_hostname(&conn->conn_to_host);
  free_idnconverted_hostname(&conn->http_proxy.host);
  free_idnconverted_hostname(&conn->socks_proxy.host);

  Curl_safefree(conn->user);
  Curl_safefree(conn->passwd);
  Curl_safefree(conn->oauth_bearer);
  Curl_safefree(conn->sasl_authzid);
  Curl_safefree(conn->options);
  Curl_safefree(conn->http_proxy.user);
  Curl_safefree(conn->socks_proxy.user);
  Curl_safefree(conn->http_proxy.passwd);
  Curl_safefree(conn->socks_proxy.passwd);
  Curl_safefree(conn->allocptr.proxyuserpwd);
  Curl_safefree(conn->allocptr.uagent);
  Curl_safefree(conn->allocptr.userpwd);
  Curl_safefree(conn->allocptr.accept_encoding);
  Curl_safefree(conn->allocptr.te);
  Curl_safefree(conn->allocptr.rangeline);
  Curl_safefree(conn->allocptr.ref);
  Curl_safefree(conn->allocptr.host);
  Curl_safefree(conn->allocptr.cookiehost);
  Curl_safefree(conn->allocptr.rtsp_transport);
  Curl_safefree(conn->trailer);
  Curl_safefree(conn->host.rawalloc); /* host name buffer */
  Curl_safefree(conn->conn_to_host.rawalloc); /* host name buffer */
  Curl_safefree(conn->hostname_resolve);
  Curl_safefree(conn->secondaryhostname);
  Curl_safefree(conn->http_proxy.host.rawalloc); /* http proxy name buffer */
  Curl_safefree(conn->socks_proxy.host.rawalloc); /* socks proxy name buffer */
  Curl_safefree(conn->connect_state);

  conn_reset_all_postponed_data(conn);
  Curl_llist_destroy(&conn->easyq, NULL);
  Curl_safefree(conn->localdev);
  Curl_free_primary_ssl_config(&conn->ssl_config);
  Curl_free_primary_ssl_config(&conn->proxy_ssl_config);

#ifdef USE_UNIX_SOCKETS
  Curl_safefree(conn->unix_domain_socket);
#endif

#ifdef USE_SSL
  Curl_safefree(conn->ssl_extra);
#endif
  free(conn); /* free all the connection oriented data */
}