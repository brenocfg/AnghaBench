#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  connect_only; int /*<<< orphan*/  ftp_use_eprt; int /*<<< orphan*/  ftp_use_epsv; void* user_passwd; int /*<<< orphan*/  tunnel_proxy; void* proxy_user_passwd; void* socksproxy; void* proxy; void* httpproxy; } ;
struct TYPE_17__ {int /*<<< orphan*/  verifyhost; int /*<<< orphan*/  verifypeer; int /*<<< orphan*/  verifystatus; } ;
struct TYPE_14__ {int /*<<< orphan*/  verifyhost; int /*<<< orphan*/  verifypeer; int /*<<< orphan*/  verifystatus; } ;
struct TYPE_13__ {scalar_t__ proxytype; } ;
struct TYPE_12__ {int /*<<< orphan*/  proxytype; } ;
struct connectdata {int connection_id; int port; int remote_port; struct connectdata* localdev; int /*<<< orphan*/  easyq; int /*<<< orphan*/  closesocket_client; int /*<<< orphan*/  fclosesocket; int /*<<< orphan*/  localport; int /*<<< orphan*/  localportrange; TYPE_9__ bits; int /*<<< orphan*/  ip_version; TYPE_6__ proxy_ssl_config; TYPE_3__ ssl_config; TYPE_2__ http_proxy; TYPE_1__ socks_proxy; struct Curl_easy* data; int /*<<< orphan*/  upkeep_interval_ms; void* keepalive; void* created; void** tempsock; void** sock; int /*<<< orphan*/ * handler; } ;
struct TYPE_18__ {int /*<<< orphan*/  verifyhost; int /*<<< orphan*/  verifypeer; int /*<<< orphan*/  verifystatus; } ;
struct TYPE_19__ {TYPE_7__ primary; } ;
struct TYPE_15__ {int /*<<< orphan*/  verifyhost; int /*<<< orphan*/  verifypeer; int /*<<< orphan*/  verifystatus; } ;
struct TYPE_16__ {TYPE_4__ primary; } ;
struct TYPE_11__ {scalar_t__ proxytype; int /*<<< orphan*/  closesocket_client; int /*<<< orphan*/  fclosesocket; int /*<<< orphan*/  localport; int /*<<< orphan*/  localportrange; scalar_t__** str; int /*<<< orphan*/  connect_only; int /*<<< orphan*/  ipver; TYPE_8__ proxy_ssl; TYPE_5__ ssl; int /*<<< orphan*/  ftp_use_eprt; int /*<<< orphan*/  ftp_use_epsv; int /*<<< orphan*/  tunnel_thru_httpproxy; int /*<<< orphan*/  upkeep_interval_ms; } ;
struct Curl_easy {TYPE_10__ set; } ;
typedef  int /*<<< orphan*/  curl_llist_dtor ;

/* Variables and functions */
 scalar_t__ CURLPROXY_HTTP ; 
 scalar_t__ CURLPROXY_HTTPS ; 
 scalar_t__ CURLPROXY_HTTP_1_0 ; 
 int /*<<< orphan*/  CURLPROXY_SOCKS4 ; 
 void* CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_handler_dummy ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* Curl_now () ; 
 void* FALSE ; 
 size_t FIRSTSOCKET ; 
 size_t SECONDARYSOCKET ; 
 size_t STRING_DEVICE ; 
 size_t STRING_PRE_PROXY ; 
 size_t STRING_PROXY ; 
 size_t STRING_PROXYUSERNAME ; 
 size_t STRING_USERNAME ; 
 void* TRUE ; 
 struct connectdata* calloc (int,int) ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  free (struct connectdata*) ; 
 scalar_t__ llist_dtor ; 
 struct connectdata* strdup (scalar_t__*) ; 

__attribute__((used)) static struct connectdata *allocate_conn(struct Curl_easy *data)
{
  struct connectdata *conn = calloc(1, sizeof(struct connectdata));
  if(!conn)
    return NULL;

#ifdef USE_SSL
  /* The SSL backend-specific data (ssl_backend_data) objects are allocated as
     a separate array to ensure suitable alignment.
     Note that these backend pointers can be swapped by vtls (eg ssl backend
     data becomes proxy backend data). */
  {
    size_t sslsize = Curl_ssl->sizeof_ssl_backend_data;
    char *ssl = calloc(4, sslsize);
    if(!ssl) {
      free(conn);
      return NULL;
    }
    conn->ssl_extra = ssl;
    conn->ssl[0].backend = (void *)ssl;
    conn->ssl[1].backend = (void *)(ssl + sslsize);
    conn->proxy_ssl[0].backend = (void *)(ssl + 2 * sslsize);
    conn->proxy_ssl[1].backend = (void *)(ssl + 3 * sslsize);
  }
#endif

  conn->handler = &Curl_handler_dummy;  /* Be sure we have a handler defined
                                           already from start to avoid NULL
                                           situations and checks */

  /* and we setup a few fields in case we end up actually using this struct */

  conn->sock[FIRSTSOCKET] = CURL_SOCKET_BAD;     /* no file descriptor */
  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD; /* no file descriptor */
  conn->tempsock[0] = CURL_SOCKET_BAD; /* no file descriptor */
  conn->tempsock[1] = CURL_SOCKET_BAD; /* no file descriptor */
  conn->connection_id = -1;    /* no ID */
  conn->port = -1; /* unknown at this point */
  conn->remote_port = -1; /* unknown at this point */
#if defined(USE_RECV_BEFORE_SEND_WORKAROUND) && defined(DEBUGBUILD)
  conn->postponed[0].bindsock = CURL_SOCKET_BAD; /* no file descriptor */
  conn->postponed[1].bindsock = CURL_SOCKET_BAD; /* no file descriptor */
#endif /* USE_RECV_BEFORE_SEND_WORKAROUND && DEBUGBUILD */

  /* Default protocol-independent behavior doesn't support persistent
     connections, so we set this to force-close. Protocols that support
     this need to set this to FALSE in their "curl_do" functions. */
  connclose(conn, "Default to force-close");

  /* Store creation time to help future close decision making */
  conn->created = Curl_now();

  /* Store current time to give a baseline to keepalive connection times. */
  conn->keepalive = Curl_now();

  /* Store off the configured connection upkeep time. */
  conn->upkeep_interval_ms = data->set.upkeep_interval_ms;

  conn->data = data; /* Setup the association between this connection
                        and the Curl_easy */

  conn->http_proxy.proxytype = data->set.proxytype;
  conn->socks_proxy.proxytype = CURLPROXY_SOCKS4;

#ifdef CURL_DISABLE_PROXY

  conn->bits.proxy = FALSE;
  conn->bits.httpproxy = FALSE;
  conn->bits.socksproxy = FALSE;
  conn->bits.proxy_user_passwd = FALSE;
  conn->bits.tunnel_proxy = FALSE;

#else /* CURL_DISABLE_PROXY */

  /* note that these two proxy bits are now just on what looks to be
     requested, they may be altered down the road */
  conn->bits.proxy = (data->set.str[STRING_PROXY] &&
                      *data->set.str[STRING_PROXY]) ? TRUE : FALSE;
  conn->bits.httpproxy = (conn->bits.proxy &&
                          (conn->http_proxy.proxytype == CURLPROXY_HTTP ||
                           conn->http_proxy.proxytype == CURLPROXY_HTTP_1_0 ||
                           conn->http_proxy.proxytype == CURLPROXY_HTTPS)) ?
                           TRUE : FALSE;
  conn->bits.socksproxy = (conn->bits.proxy &&
                           !conn->bits.httpproxy) ? TRUE : FALSE;

  if(data->set.str[STRING_PRE_PROXY] && *data->set.str[STRING_PRE_PROXY]) {
    conn->bits.proxy = TRUE;
    conn->bits.socksproxy = TRUE;
  }

  conn->bits.proxy_user_passwd =
    (data->set.str[STRING_PROXYUSERNAME]) ? TRUE : FALSE;
  conn->bits.tunnel_proxy = data->set.tunnel_thru_httpproxy;

#endif /* CURL_DISABLE_PROXY */

  conn->bits.user_passwd = (data->set.str[STRING_USERNAME]) ? TRUE : FALSE;
  conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
  conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;

  conn->ssl_config.verifystatus = data->set.ssl.primary.verifystatus;
  conn->ssl_config.verifypeer = data->set.ssl.primary.verifypeer;
  conn->ssl_config.verifyhost = data->set.ssl.primary.verifyhost;
  conn->proxy_ssl_config.verifystatus =
    data->set.proxy_ssl.primary.verifystatus;
  conn->proxy_ssl_config.verifypeer = data->set.proxy_ssl.primary.verifypeer;
  conn->proxy_ssl_config.verifyhost = data->set.proxy_ssl.primary.verifyhost;
  conn->ip_version = data->set.ipver;
  conn->bits.connect_only = data->set.connect_only;

#if !defined(CURL_DISABLE_HTTP) && defined(USE_NTLM) && \
    defined(NTLM_WB_ENABLED)
  conn->ntlm_auth_hlpr_socket = CURL_SOCKET_BAD;
  conn->ntlm_auth_hlpr_pid = 0;
  conn->challenge_header = NULL;
  conn->response_header = NULL;
#endif

  /* Initialize the easy handle list */
  Curl_llist_init(&conn->easyq, (curl_llist_dtor) llist_dtor);

#ifdef HAVE_GSSAPI
  conn->data_prot = PROT_CLEAR;
#endif

  /* Store the local bind parameters that will be used for this connection */
  if(data->set.str[STRING_DEVICE]) {
    conn->localdev = strdup(data->set.str[STRING_DEVICE]);
    if(!conn->localdev)
      goto error;
  }
  conn->localportrange = data->set.localportrange;
  conn->localport = data->set.localport;

  /* the close socket stuff needs to be copied to the connection struct as
     it may live on without (this specific) Curl_easy */
  conn->fclosesocket = data->set.fclosesocket;
  conn->closesocket_client = data->set.closesocket_client;

  return conn;
  error:

  Curl_llist_destroy(&conn->easyq, NULL);
  free(conn->localdev);
#ifdef USE_SSL
  free(conn->ssl_extra);
#endif
  free(conn);
  return NULL;
}