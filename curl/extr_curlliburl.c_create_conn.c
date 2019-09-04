#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  dispname; scalar_t__ name; } ;
struct TYPE_14__ {int conn_to_host; scalar_t__ socksproxy; scalar_t__ httpproxy; void* tls_enable_npn; void* tls_enable_alpn; scalar_t__ proxy; void** tcpconnect; int /*<<< orphan*/  tcp_fastopen; void* tunnel_proxy; void* conn_to_port; } ;
struct TYPE_25__ {TYPE_11__ host; } ;
struct TYPE_24__ {TYPE_11__ host; } ;
struct connectdata {scalar_t__ conn_to_port; scalar_t__ remote_port; TYPE_11__ conn_to_host; TYPE_10__ bits; TYPE_9__ socks_proxy; TYPE_8__ http_proxy; TYPE_11__ host; int /*<<< orphan*/  seek_client; int /*<<< orphan*/  seek_func; TYPE_5__* handler; int /*<<< orphan*/  connection_id; scalar_t__ (* passwd ) (struct connectdata*,int*) ;scalar_t__ (* user ) (struct connectdata*,int*) ;int /*<<< orphan*/  proxy_ssl_config; int /*<<< orphan*/  ssl_config; void** send; void** recv; int /*<<< orphan*/  options; TYPE_2__* given; int /*<<< orphan*/  oauth_bearer; } ;
struct connectbundle {size_t num_connections; } ;
struct TYPE_16__ {scalar_t__ clientcert; scalar_t__ cipher_list13; scalar_t__ cipher_list; scalar_t__ egdsocket; scalar_t__ random_file; scalar_t__ CAfile; scalar_t__ CApath; } ;
struct TYPE_20__ {TYPE_13__ primary; scalar_t__ key_passwd; scalar_t__ key_type; scalar_t__ key; scalar_t__ cert_type; scalar_t__ cert; scalar_t__ issuercert; scalar_t__ CRLfile; } ;
struct TYPE_19__ {TYPE_13__ primary; scalar_t__ key_passwd; scalar_t__ key_type; scalar_t__ key; scalar_t__ cert_type; scalar_t__ cert; scalar_t__ issuercert; scalar_t__ CRLfile; } ;
struct TYPE_23__ {int /*<<< orphan*/  seek_client; int /*<<< orphan*/  seek_func; scalar_t__ ssl_enable_npn; scalar_t__ ssl_enable_alpn; scalar_t__ connect_only; scalar_t__ reuse_fresh; TYPE_4__ proxy_ssl; TYPE_3__ ssl; scalar_t__* str; int /*<<< orphan*/  tcp_fastopen; int /*<<< orphan*/  connect_to; } ;
struct TYPE_22__ {int /*<<< orphan*/  conn_cache; int /*<<< orphan*/  this_is_a_follow; } ;
struct TYPE_17__ {int /*<<< orphan*/  url; } ;
struct Curl_easy {TYPE_7__ set; TYPE_6__ state; TYPE_1__ change; int /*<<< orphan*/  multi; } ;
struct TYPE_21__ {int flags; scalar_t__ (* done ) (struct connectdata*,scalar_t__,void*) ;scalar_t__ (* connect_it ) (struct connectdata*,int*) ;} ;
struct TYPE_18__ {int flags; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 size_t CONN_INUSE (struct connectdata*) ; 
 scalar_t__ CURLE_NO_CONNECTION_AVAILABLE ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_URL_MALFORMAT ; 
 int ConnectionExists (struct Curl_easy*,struct connectdata*,struct connectdata**,int*,int*) ; 
 int /*<<< orphan*/  Curl_attach_connnection (struct Curl_easy*,struct connectdata*) ; 
 int /*<<< orphan*/  Curl_clone_primary_ssl_config (TYPE_13__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_conncache_add_conn (int /*<<< orphan*/ ,struct connectdata*) ; 
 size_t Curl_conncache_bundle_size (struct connectdata*) ; 
 struct connectdata* Curl_conncache_extract_bundle (struct Curl_easy*,struct connectbundle*) ; 
 struct connectdata* Curl_conncache_extract_oldest (struct Curl_easy*) ; 
 struct connectbundle* Curl_conncache_find_bundle (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_conncache_return_conn (struct connectdata*) ; 
 size_t Curl_conncache_size (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_conncache_unlock (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_disconnect (struct Curl_easy*,struct connectdata*,void*) ; 
 int /*<<< orphan*/  Curl_init_do (struct Curl_easy*,struct connectdata*) ; 
 size_t Curl_multi_max_host_connections (int /*<<< orphan*/ ) ; 
 size_t Curl_multi_max_total_connections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_persistconninfo (struct connectdata*) ; 
 void* Curl_recv_plain ; 
 void* Curl_send_plain ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,int,int,void*,int) ; 
 int /*<<< orphan*/  DEBUGASSERT (scalar_t__ (*) (struct connectdata*,int*)) ; 
 void* FALSE ; 
 size_t FIRSTSOCKET ; 
 scalar_t__ IsMultiplexingPossible (struct Curl_easy*,struct connectdata*) ; 
 int PROTOPT_ALPN_NPN ; 
 int PROTOPT_NONETWORK ; 
 int PROTOPT_SSL ; 
 size_t SECONDARYSOCKET ; 
 size_t STRING_BEARER ; 
 size_t STRING_CERT_ORIG ; 
 size_t STRING_CERT_PROXY ; 
 size_t STRING_CERT_TYPE_ORIG ; 
 size_t STRING_CERT_TYPE_PROXY ; 
 size_t STRING_KEY_ORIG ; 
 size_t STRING_KEY_PASSWD_ORIG ; 
 size_t STRING_KEY_PASSWD_PROXY ; 
 size_t STRING_KEY_PROXY ; 
 size_t STRING_KEY_TYPE_ORIG ; 
 size_t STRING_KEY_TYPE_PROXY ; 
 size_t STRING_SSL_CAFILE_ORIG ; 
 size_t STRING_SSL_CAFILE_PROXY ; 
 size_t STRING_SSL_CAPATH_ORIG ; 
 size_t STRING_SSL_CAPATH_PROXY ; 
 size_t STRING_SSL_CIPHER13_LIST_ORIG ; 
 size_t STRING_SSL_CIPHER13_LIST_PROXY ; 
 size_t STRING_SSL_CIPHER_LIST_ORIG ; 
 size_t STRING_SSL_CIPHER_LIST_PROXY ; 
 size_t STRING_SSL_CRLFILE_ORIG ; 
 size_t STRING_SSL_CRLFILE_PROXY ; 
 size_t STRING_SSL_EGDSOCKET ; 
 size_t STRING_SSL_ISSUERCERT_ORIG ; 
 size_t STRING_SSL_ISSUERCERT_PROXY ; 
 size_t STRING_SSL_RANDOM_FILE ; 
 void* TRUE ; 
 struct connectdata* allocate_conn (struct Curl_easy*) ; 
 int /*<<< orphan*/  conn_free (struct connectdata*) ; 
 scalar_t__ create_conn_helper_init_proxy (struct connectdata*) ; 
 int /*<<< orphan*/  free (struct connectdata*) ; 
 scalar_t__ idnconvert_hostname (struct connectdata*,TYPE_11__*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 scalar_t__ override_login (struct Curl_easy*,struct connectdata*,scalar_t__ (*) (struct connectdata*,int*),scalar_t__ (*) (struct connectdata*,int*),int /*<<< orphan*/ *) ; 
 scalar_t__ parse_connect_to_slist (struct Curl_easy*,struct connectdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_remote_port (struct Curl_easy*,struct connectdata*) ; 
 scalar_t__ parseurlandfillconn (struct Curl_easy*,struct connectdata*) ; 
 int /*<<< orphan*/  prune_dead_connections (struct Curl_easy*) ; 
 scalar_t__ resolve_server (struct Curl_easy*,struct connectdata*,int*) ; 
 int /*<<< orphan*/  reuse_conn (struct connectdata*,struct connectdata*) ; 
 scalar_t__ set_login (struct connectdata*) ; 
 scalar_t__ setup_connection_internals (struct connectdata*) ; 
 scalar_t__ setup_range (struct Curl_easy*) ; 
 scalar_t__ strcasecompare (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 
 int /*<<< orphan*/  strip_trailing_dot (TYPE_11__*) ; 
 scalar_t__ stub1 (struct connectdata*,int*) ; 
 scalar_t__ stub2 (struct connectdata*,scalar_t__,void*) ; 

__attribute__((used)) static CURLcode create_conn(struct Curl_easy *data,
                            struct connectdata **in_connect,
                            bool *async)
{
  CURLcode result = CURLE_OK;
  struct connectdata *conn;
  struct connectdata *conn_temp = NULL;
  bool reuse;
  bool connections_available = TRUE;
  bool force_reuse = FALSE;
  bool waitpipe = FALSE;
  size_t max_host_connections = Curl_multi_max_host_connections(data->multi);
  size_t max_total_connections = Curl_multi_max_total_connections(data->multi);

  *async = FALSE;
  *in_connect = NULL;

  /*************************************************************
   * Check input data
   *************************************************************/
  if(!data->change.url) {
    result = CURLE_URL_MALFORMAT;
    goto out;
  }

  /* First, split up the current URL in parts so that we can use the
     parts for checking against the already present connections. In order
     to not have to modify everything at once, we allocate a temporary
     connection data struct and fill in for comparison purposes. */
  conn = allocate_conn(data);

  if(!conn) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  /* We must set the return variable as soon as possible, so that our
     parent can cleanup any possible allocs we may have done before
     any failure */
  *in_connect = conn;

  result = parseurlandfillconn(data, conn);
  if(result)
    goto out;

  if(data->set.str[STRING_BEARER]) {
    conn->oauth_bearer = strdup(data->set.str[STRING_BEARER]);
    if(!conn->oauth_bearer) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }
  }

#ifdef USE_UNIX_SOCKETS
  if(data->set.str[STRING_UNIX_SOCKET_PATH]) {
    conn->unix_domain_socket = strdup(data->set.str[STRING_UNIX_SOCKET_PATH]);
    if(conn->unix_domain_socket == NULL) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }
    conn->abstract_unix_socket = data->set.abstract_unix_socket;
  }
#endif

  /* After the unix socket init but before the proxy vars are used, parse and
     initialize the proxy vars */
#ifndef CURL_DISABLE_PROXY
  result = create_conn_helper_init_proxy(conn);
  if(result)
    goto out;
#endif

  /*************************************************************
   * If the protocol is using SSL and HTTP proxy is used, we set
   * the tunnel_proxy bit.
   *************************************************************/
  if((conn->given->flags&PROTOPT_SSL) && conn->bits.httpproxy)
    conn->bits.tunnel_proxy = TRUE;

  /*************************************************************
   * Figure out the remote port number and fix it in the URL
   *************************************************************/
  result = parse_remote_port(data, conn);
  if(result)
    goto out;

  /* Check for overridden login details and set them accordingly so they
     they are known when protocol->setup_connection is called! */
  result = override_login(data, conn, &conn->user, &conn->passwd,
                          &conn->options);
  if(result)
    goto out;

  result = set_login(conn); /* default credentials */
  if(result)
    goto out;

  /*************************************************************
   * Process the "connect to" linked list of hostname/port mappings.
   * Do this after the remote port number has been fixed in the URL.
   *************************************************************/
  result = parse_connect_to_slist(data, conn, data->set.connect_to);
  if(result)
    goto out;

  /*************************************************************
   * IDN-convert the hostnames
   *************************************************************/
  result = idnconvert_hostname(conn, &conn->host);
  if(result)
    goto out;
  if(conn->bits.conn_to_host) {
    result = idnconvert_hostname(conn, &conn->conn_to_host);
    if(result)
      goto out;
  }
  if(conn->bits.httpproxy) {
    result = idnconvert_hostname(conn, &conn->http_proxy.host);
    if(result)
      goto out;
  }
  if(conn->bits.socksproxy) {
    result = idnconvert_hostname(conn, &conn->socks_proxy.host);
    if(result)
      goto out;
  }

  /*************************************************************
   * Check whether the host and the "connect to host" are equal.
   * Do this after the hostnames have been IDN-converted.
   *************************************************************/
  if(conn->bits.conn_to_host &&
     strcasecompare(conn->conn_to_host.name, conn->host.name)) {
    conn->bits.conn_to_host = FALSE;
  }

  /*************************************************************
   * Check whether the port and the "connect to port" are equal.
   * Do this after the remote port number has been fixed in the URL.
   *************************************************************/
  if(conn->bits.conn_to_port && conn->conn_to_port == conn->remote_port) {
    conn->bits.conn_to_port = FALSE;
  }

  /*************************************************************
   * If the "connect to" feature is used with an HTTP proxy,
   * we set the tunnel_proxy bit.
   *************************************************************/
  if((conn->bits.conn_to_host || conn->bits.conn_to_port) &&
      conn->bits.httpproxy)
    conn->bits.tunnel_proxy = TRUE;

  /*************************************************************
   * Setup internals depending on protocol. Needs to be done after
   * we figured out what/if proxy to use.
   *************************************************************/
  result = setup_connection_internals(conn);
  if(result)
    goto out;

  conn->recv[FIRSTSOCKET] = Curl_recv_plain;
  conn->send[FIRSTSOCKET] = Curl_send_plain;
  conn->recv[SECONDARYSOCKET] = Curl_recv_plain;
  conn->send[SECONDARYSOCKET] = Curl_send_plain;

  conn->bits.tcp_fastopen = data->set.tcp_fastopen;

  /***********************************************************************
   * file: is a special case in that it doesn't need a network connection
   ***********************************************************************/
#ifndef CURL_DISABLE_FILE
  if(conn->handler->flags & PROTOPT_NONETWORK) {
    bool done;
    /* this is supposed to be the connect function so we better at least check
       that the file is present here! */
    DEBUGASSERT(conn->handler->connect_it);
    Curl_persistconninfo(conn);
    result = conn->handler->connect_it(conn, &done);

    /* Setup a "faked" transfer that'll do nothing */
    if(!result) {
      conn->bits.tcpconnect[FIRSTSOCKET] = TRUE; /* we are "connected */

      result = Curl_conncache_add_conn(data->state.conn_cache, conn);
      if(result)
        goto out;

      /*
       * Setup whatever necessary for a resumed transfer
       */
      result = setup_range(data);
      if(result) {
        DEBUGASSERT(conn->handler->done);
        /* we ignore the return code for the protocol-specific DONE */
        (void)conn->handler->done(conn, result, FALSE);
        goto out;
      }
      Curl_attach_connnection(data, conn);
      Curl_setup_transfer(data, -1, -1, FALSE, -1);
    }

    /* since we skip do_init() */
    Curl_init_do(data, conn);

    goto out;
  }
#endif

  /* Get a cloned copy of the SSL config situation stored in the
     connection struct. But to get this going nicely, we must first make
     sure that the strings in the master copy are pointing to the correct
     strings in the session handle strings array!

     Keep in mind that the pointers in the master copy are pointing to strings
     that will be freed as part of the Curl_easy struct, but all cloned
     copies will be separately allocated.
  */
  data->set.ssl.primary.CApath = data->set.str[STRING_SSL_CAPATH_ORIG];
  data->set.proxy_ssl.primary.CApath = data->set.str[STRING_SSL_CAPATH_PROXY];
  data->set.ssl.primary.CAfile = data->set.str[STRING_SSL_CAFILE_ORIG];
  data->set.proxy_ssl.primary.CAfile = data->set.str[STRING_SSL_CAFILE_PROXY];
  data->set.ssl.primary.random_file = data->set.str[STRING_SSL_RANDOM_FILE];
  data->set.proxy_ssl.primary.random_file =
    data->set.str[STRING_SSL_RANDOM_FILE];
  data->set.ssl.primary.egdsocket = data->set.str[STRING_SSL_EGDSOCKET];
  data->set.proxy_ssl.primary.egdsocket = data->set.str[STRING_SSL_EGDSOCKET];
  data->set.ssl.primary.cipher_list =
    data->set.str[STRING_SSL_CIPHER_LIST_ORIG];
  data->set.proxy_ssl.primary.cipher_list =
    data->set.str[STRING_SSL_CIPHER_LIST_PROXY];
  data->set.ssl.primary.cipher_list13 =
    data->set.str[STRING_SSL_CIPHER13_LIST_ORIG];
  data->set.proxy_ssl.primary.cipher_list13 =
    data->set.str[STRING_SSL_CIPHER13_LIST_PROXY];

  data->set.ssl.CRLfile = data->set.str[STRING_SSL_CRLFILE_ORIG];
  data->set.proxy_ssl.CRLfile = data->set.str[STRING_SSL_CRLFILE_PROXY];
  data->set.ssl.issuercert = data->set.str[STRING_SSL_ISSUERCERT_ORIG];
  data->set.proxy_ssl.issuercert = data->set.str[STRING_SSL_ISSUERCERT_PROXY];
  data->set.ssl.cert = data->set.str[STRING_CERT_ORIG];
  data->set.proxy_ssl.cert = data->set.str[STRING_CERT_PROXY];
  data->set.ssl.cert_type = data->set.str[STRING_CERT_TYPE_ORIG];
  data->set.proxy_ssl.cert_type = data->set.str[STRING_CERT_TYPE_PROXY];
  data->set.ssl.key = data->set.str[STRING_KEY_ORIG];
  data->set.proxy_ssl.key = data->set.str[STRING_KEY_PROXY];
  data->set.ssl.key_type = data->set.str[STRING_KEY_TYPE_ORIG];
  data->set.proxy_ssl.key_type = data->set.str[STRING_KEY_TYPE_PROXY];
  data->set.ssl.key_passwd = data->set.str[STRING_KEY_PASSWD_ORIG];
  data->set.proxy_ssl.key_passwd = data->set.str[STRING_KEY_PASSWD_PROXY];
  data->set.ssl.primary.clientcert = data->set.str[STRING_CERT_ORIG];
  data->set.proxy_ssl.primary.clientcert = data->set.str[STRING_CERT_PROXY];
#ifdef USE_TLS_SRP
  data->set.ssl.username = data->set.str[STRING_TLSAUTH_USERNAME_ORIG];
  data->set.proxy_ssl.username = data->set.str[STRING_TLSAUTH_USERNAME_PROXY];
  data->set.ssl.password = data->set.str[STRING_TLSAUTH_PASSWORD_ORIG];
  data->set.proxy_ssl.password = data->set.str[STRING_TLSAUTH_PASSWORD_PROXY];
#endif

  if(!Curl_clone_primary_ssl_config(&data->set.ssl.primary,
     &conn->ssl_config)) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  if(!Curl_clone_primary_ssl_config(&data->set.proxy_ssl.primary,
                                    &conn->proxy_ssl_config)) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  prune_dead_connections(data);

  /*************************************************************
   * Check the current list of connections to see if we can
   * re-use an already existing one or if we have to create a
   * new one.
   *************************************************************/

  DEBUGASSERT(conn->user);
  DEBUGASSERT(conn->passwd);

  /* reuse_fresh is TRUE if we are told to use a new connection by force, but
     we only acknowledge this option if this is not a re-used connection
     already (which happens due to follow-location or during a HTTP
     authentication phase). CONNECT_ONLY transfers also refuse reuse. */
  if((data->set.reuse_fresh && !data->state.this_is_a_follow) ||
     data->set.connect_only)
    reuse = FALSE;
  else
    reuse = ConnectionExists(data, conn, &conn_temp, &force_reuse, &waitpipe);

  /* If we found a reusable connection that is now marked as in use, we may
     still want to open a new connection if we are multiplexing. */
  if(reuse && !force_reuse && IsMultiplexingPossible(data, conn_temp)) {
    size_t multiplexed = CONN_INUSE(conn_temp);
    if(multiplexed > 0) {
      infof(data, "Found connection %ld, with %zu requests on it\n",
            conn_temp->connection_id, multiplexed);

      if(Curl_conncache_bundle_size(conn_temp) < max_host_connections &&
         Curl_conncache_size(data) < max_total_connections) {
        /* We want a new connection anyway */
        reuse = FALSE;

        infof(data, "We can reuse, but we want a new connection anyway\n");
        Curl_conncache_return_conn(conn_temp);
      }
    }
  }

  if(reuse) {
    /*
     * We already have a connection for this, we got the former connection
     * in the conn_temp variable and thus we need to cleanup the one we
     * just allocated before we can move along and use the previously
     * existing one.
     */
    reuse_conn(conn, conn_temp);
#ifdef USE_SSL
    free(conn->ssl_extra);
#endif
    free(conn);          /* we don't need this anymore */
    conn = conn_temp;
    *in_connect = conn;

    infof(data, "Re-using existing connection! (#%ld) with %s %s\n",
          conn->connection_id,
          conn->bits.proxy?"proxy":"host",
          conn->socks_proxy.host.name ? conn->socks_proxy.host.dispname :
          conn->http_proxy.host.name ? conn->http_proxy.host.dispname :
                                       conn->host.dispname);
  }
  else {
    /* We have decided that we want a new connection. However, we may not
       be able to do that if we have reached the limit of how many
       connections we are allowed to open. */

    if(conn->handler->flags & PROTOPT_ALPN_NPN) {
      /* The protocol wants it, so set the bits if enabled in the easy handle
         (default) */
      if(data->set.ssl_enable_alpn)
        conn->bits.tls_enable_alpn = TRUE;
      if(data->set.ssl_enable_npn)
        conn->bits.tls_enable_npn = TRUE;
    }

    if(waitpipe)
      /* There is a connection that *might* become usable for multiplexing
         "soon", and we wait for that */
      connections_available = FALSE;
    else {
      /* this gets a lock on the conncache */
      struct connectbundle *bundle =
        Curl_conncache_find_bundle(conn, data->state.conn_cache);

      if(max_host_connections > 0 && bundle &&
         (bundle->num_connections >= max_host_connections)) {
        struct connectdata *conn_candidate;

        /* The bundle is full. Extract the oldest connection. */
        conn_candidate = Curl_conncache_extract_bundle(data, bundle);
        Curl_conncache_unlock(data);

        if(conn_candidate)
          (void)Curl_disconnect(data, conn_candidate,
                                /* dead_connection */ FALSE);
        else {
          infof(data, "No more connections allowed to host: %zu\n",
                max_host_connections);
          connections_available = FALSE;
        }
      }
      else
        Curl_conncache_unlock(data);

    }

    if(connections_available &&
       (max_total_connections > 0) &&
       (Curl_conncache_size(data) >= max_total_connections)) {
      struct connectdata *conn_candidate;

      /* The cache is full. Let's see if we can kill a connection. */
      conn_candidate = Curl_conncache_extract_oldest(data);
      if(conn_candidate)
        (void)Curl_disconnect(data, conn_candidate,
                              /* dead_connection */ FALSE);
      else {
        infof(data, "No connections available in cache\n");
        connections_available = FALSE;
      }
    }

    if(!connections_available) {
      infof(data, "No connections available.\n");

      conn_free(conn);
      *in_connect = NULL;

      result = CURLE_NO_CONNECTION_AVAILABLE;
      goto out;
    }
    else {
      /*
       * This is a brand new connection, so let's store it in the connection
       * cache of ours!
       */
      result = Curl_conncache_add_conn(data->state.conn_cache, conn);
      if(result)
        goto out;
    }

#if defined(USE_NTLM)
    /* If NTLM is requested in a part of this connection, make sure we don't
       assume the state is fine as this is a fresh connection and NTLM is
       connection based. */
    if((data->state.authhost.picked & (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
       data->state.authhost.done) {
      infof(data, "NTLM picked AND auth done set, clear picked!\n");
      data->state.authhost.picked = CURLAUTH_NONE;
      data->state.authhost.done = FALSE;
    }

    if((data->state.authproxy.picked & (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
       data->state.authproxy.done) {
      infof(data, "NTLM-proxy picked AND auth done set, clear picked!\n");
      data->state.authproxy.picked = CURLAUTH_NONE;
      data->state.authproxy.done = FALSE;
    }
#endif
  }

  /* Setup and init stuff before DO starts, in preparing for the transfer. */
  Curl_init_do(data, conn);

  /*
   * Setup whatever necessary for a resumed transfer
   */
  result = setup_range(data);
  if(result)
    goto out;

  /* Continue connectdata initialization here. */

  /*
   * Inherit the proper values from the urldata struct AFTER we have arranged
   * the persistent connection stuff
   */
  conn->seek_func = data->set.seek_func;
  conn->seek_client = data->set.seek_client;

  /*************************************************************
   * Resolve the address of the server or proxy
   *************************************************************/
  result = resolve_server(data, conn, async);

  /* Strip trailing dots. resolve_server copied the name. */
  strip_trailing_dot(&conn->host);
  if(conn->bits.httpproxy)
    strip_trailing_dot(&conn->http_proxy.host);
  if(conn->bits.socksproxy)
    strip_trailing_dot(&conn->socks_proxy.host);
  if(conn->bits.conn_to_host)
    strip_trailing_dot(&conn->conn_to_host);

out:
  return result;
}