#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timediff_t ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_4__ sin_addr; } ;
struct TYPE_9__ {scalar_t__ httpproxy; } ;
struct TYPE_7__ {scalar_t__ proxytype; } ;
struct connectdata {struct Curl_easy* data; TYPE_3__ bits; TYPE_1__ socks_proxy; int /*<<< orphan*/ * sock; } ;
struct TYPE_8__ {unsigned long socks5auth; } ;
struct Curl_easy {TYPE_2__ set; } ;
struct Curl_dns_entry {TYPE_5__* addr; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {scalar_t__ ai_family; scalar_t__ ai_addr; } ;
typedef  TYPE_5__ Curl_addrinfo ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 unsigned long const CURLAUTH_BASIC ; 
 unsigned long const CURLAUTH_GSSAPI ; 
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_COULDNT_CONNECT ; 
 scalar_t__ CURLE_COULDNT_RESOLVE_HOST ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OPERATION_TIMEDOUT ; 
 scalar_t__ CURLE_RECV_ERROR ; 
 scalar_t__ CURLPROXY_SOCKS5 ; 
 int CURLRESOLV_ERROR ; 
 int CURLRESOLV_PENDING ; 
 int CURL_CSELECT_ERR ; 
 int Curl_blockread_all (struct connectdata*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  Curl_printable_address (TYPE_5__*,char*,int) ; 
 int Curl_resolv (struct connectdata*,char const*,int,struct Curl_dns_entry**) ; 
 int /*<<< orphan*/  Curl_resolv_unlock (struct Curl_easy*,struct Curl_dns_entry*) ; 
 scalar_t__ Curl_resolver_wait_resolv (struct connectdata*,struct Curl_dns_entry**) ; 
 scalar_t__ Curl_timeleft (struct Curl_easy*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Curl_write_plain (struct connectdata*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int FALSE ; 
 int SOCKET_READABLE (int /*<<< orphan*/ ,scalar_t__) ; 
 int SOCKET_WRITABLE (int /*<<< orphan*/ ,scalar_t__) ; 
 int TRUE ; 
 int /*<<< orphan*/  curlx_nonblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t const) ; 
 void* strlen (char const*) ; 

CURLcode Curl_SOCKS5(const char *proxy_user,
                     const char *proxy_password,
                     const char *hostname,
                     int remote_port,
                     int sockindex,
                     struct connectdata *conn)
{
  /*
    According to the RFC1928, section "6.  Replies". This is what a SOCK5
    replies:

        +----+-----+-------+------+----------+----------+
        |VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT |
        +----+-----+-------+------+----------+----------+
        | 1  |  1  | X'00' |  1   | Variable |    2     |
        +----+-----+-------+------+----------+----------+

    Where:

    o  VER    protocol version: X'05'
    o  REP    Reply field:
    o  X'00' succeeded
  */

  unsigned char socksreq[600]; /* room for large user/pw (255 max each) */
  int idx;
  ssize_t actualread;
  ssize_t written;
  int result;
  CURLcode code;
  curl_socket_t sock = conn->sock[sockindex];
  struct Curl_easy *data = conn->data;
  timediff_t timeout;
  bool socks5_resolve_local =
    (conn->socks_proxy.proxytype == CURLPROXY_SOCKS5) ? TRUE : FALSE;
  const size_t hostname_len = strlen(hostname);
  ssize_t len = 0;
  const unsigned long auth = data->set.socks5auth;
  bool allow_gssapi = FALSE;

  if(conn->bits.httpproxy)
    infof(conn->data, "SOCKS5: connecting to HTTP proxy %s port %d\n",
          hostname, remote_port);

  /* RFC1928 chapter 5 specifies max 255 chars for domain name in packet */
  if(!socks5_resolve_local && hostname_len > 255) {
    infof(conn->data, "SOCKS5: server resolving disabled for hostnames of "
          "length > 255 [actual len=%zu]\n", hostname_len);
    socks5_resolve_local = TRUE;
  }

  /* get timeout */
  timeout = Curl_timeleft(data, NULL, TRUE);

  if(timeout < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  (void)curlx_nonblock(sock, TRUE);

  /* wait until socket gets connected */
  result = SOCKET_WRITABLE(sock, timeout);

  if(-1 == result) {
    failf(conn->data, "SOCKS5: no connection here");
    return CURLE_COULDNT_CONNECT;
  }
  if(0 == result) {
    failf(conn->data, "SOCKS5: connection timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(result & CURL_CSELECT_ERR) {
    failf(conn->data, "SOCKS5: error occurred during connection");
    return CURLE_COULDNT_CONNECT;
  }

  if(auth & ~(CURLAUTH_BASIC | CURLAUTH_GSSAPI))
    infof(conn->data,
        "warning: unsupported value passed to CURLOPT_SOCKS5_AUTH: %lu\n",
        auth);
  if(!(auth & CURLAUTH_BASIC))
    /* disable username/password auth */
    proxy_user = NULL;
#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  if(auth & CURLAUTH_GSSAPI)
    allow_gssapi = TRUE;
#endif

  idx = 0;
  socksreq[idx++] = 5;   /* version */
  idx++;                 /* reserve for the number of authentication methods */
  socksreq[idx++] = 0;   /* no authentication */
  if(allow_gssapi)
    socksreq[idx++] = 1; /* GSS-API */
  if(proxy_user)
    socksreq[idx++] = 2; /* username/password */
  /* write the number of authentication methods */
  socksreq[1] = (unsigned char) (idx - 2);

  (void)curlx_nonblock(sock, FALSE);

  infof(data, "SOCKS5 communication to %s:%d\n", hostname, remote_port);

  code = Curl_write_plain(conn, sock, (char *)socksreq, (2 + (int)socksreq[1]),
                          &written);
  if(code || (written != (2 + (int)socksreq[1]))) {
    failf(data, "Unable to send initial SOCKS5 request.");
    return CURLE_COULDNT_CONNECT;
  }

  (void)curlx_nonblock(sock, TRUE);

  result = SOCKET_READABLE(sock, timeout);

  if(-1 == result) {
    failf(conn->data, "SOCKS5 nothing to read");
    return CURLE_COULDNT_CONNECT;
  }
  if(0 == result) {
    failf(conn->data, "SOCKS5 read timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(result & CURL_CSELECT_ERR) {
    failf(conn->data, "SOCKS5 read error occurred");
    return CURLE_RECV_ERROR;
  }

  (void)curlx_nonblock(sock, FALSE);

  result = Curl_blockread_all(conn, sock, (char *)socksreq, 2, &actualread);
  if(result || (actualread != 2)) {
    failf(data, "Unable to receive initial SOCKS5 response.");
    return CURLE_COULDNT_CONNECT;
  }

  if(socksreq[0] != 5) {
    failf(data, "Received invalid version in initial SOCKS5 response.");
    return CURLE_COULDNT_CONNECT;
  }
  if(socksreq[1] == 0) {
    /* Nothing to do, no authentication needed */
    ;
  }
#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  else if(allow_gssapi && (socksreq[1] == 1)) {
    code = Curl_SOCKS5_gssapi_negotiate(sockindex, conn);
    if(code) {
      failf(data, "Unable to negotiate SOCKS5 GSS-API context.");
      return CURLE_COULDNT_CONNECT;
    }
  }
#endif
  else if(socksreq[1] == 2) {
    /* Needs user name and password */
    size_t proxy_user_len, proxy_password_len;
    if(proxy_user && proxy_password) {
      proxy_user_len = strlen(proxy_user);
      proxy_password_len = strlen(proxy_password);
    }
    else {
      proxy_user_len = 0;
      proxy_password_len = 0;
    }

    /*   username/password request looks like
     * +----+------+----------+------+----------+
     * |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
     * +----+------+----------+------+----------+
     * | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
     * +----+------+----------+------+----------+
     */
    len = 0;
    socksreq[len++] = 1;    /* username/pw subnegotiation version */
    socksreq[len++] = (unsigned char) proxy_user_len;
    if(proxy_user && proxy_user_len) {
      /* the length must fit in a single byte */
      if(proxy_user_len >= 255) {
        failf(data, "Excessive user name length for proxy auth");
        return CURLE_BAD_FUNCTION_ARGUMENT;
      }
      memcpy(socksreq + len, proxy_user, proxy_user_len);
    }
    len += proxy_user_len;
    socksreq[len++] = (unsigned char) proxy_password_len;
    if(proxy_password && proxy_password_len) {
      /* the length must fit in a single byte */
      if(proxy_password_len > 255) {
        failf(data, "Excessive password length for proxy auth");
        return CURLE_BAD_FUNCTION_ARGUMENT;
      }
      memcpy(socksreq + len, proxy_password, proxy_password_len);
    }
    len += proxy_password_len;

    code = Curl_write_plain(conn, sock, (char *)socksreq, len, &written);
    if(code || (len != written)) {
      failf(data, "Failed to send SOCKS5 sub-negotiation request.");
      return CURLE_COULDNT_CONNECT;
    }

    result = Curl_blockread_all(conn, sock, (char *)socksreq, 2, &actualread);
    if(result || (actualread != 2)) {
      failf(data, "Unable to receive SOCKS5 sub-negotiation response.");
      return CURLE_COULDNT_CONNECT;
    }

    /* ignore the first (VER) byte */
    if(socksreq[1] != 0) { /* status */
      failf(data, "User was rejected by the SOCKS5 server (%d %d).",
            socksreq[0], socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    }

    /* Everything is good so far, user was authenticated! */
  }
  else {
    /* error */
    if(!allow_gssapi && (socksreq[1] == 1)) {
      failf(data,
            "SOCKS5 GSSAPI per-message authentication is not supported.");
      return CURLE_COULDNT_CONNECT;
    }
    if(socksreq[1] == 255) {
      if(!proxy_user || !*proxy_user) {
        failf(data,
              "No authentication method was acceptable. (It is quite likely"
              " that the SOCKS5 server wanted a username/password, since none"
              " was supplied to the server on this connection.)");
      }
      else {
        failf(data, "No authentication method was acceptable.");
      }
      return CURLE_COULDNT_CONNECT;
    }
    else {
      failf(data,
            "Undocumented SOCKS5 mode attempted to be used by server.");
      return CURLE_COULDNT_CONNECT;
    }
  }

  /* Authentication is complete, now specify destination to the proxy */
  len = 0;
  socksreq[len++] = 5; /* version (SOCKS5) */
  socksreq[len++] = 1; /* connect */
  socksreq[len++] = 0; /* must be zero */

  if(!socks5_resolve_local) {
    socksreq[len++] = 3; /* ATYP: domain name = 3 */
    socksreq[len++] = (char) hostname_len; /* address length */
    memcpy(&socksreq[len], hostname, hostname_len); /* address str w/o NULL */
    len += hostname_len;
  }
  else {
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp = NULL;
    int rc = Curl_resolv(conn, hostname, remote_port, &dns);

    if(rc == CURLRESOLV_ERROR)
      return CURLE_COULDNT_RESOLVE_HOST;

    if(rc == CURLRESOLV_PENDING) {
      /* this requires that we're in "wait for resolve" state */
      code = Curl_resolver_wait_resolv(conn, &dns);
      if(code)
        return code;
    }

    /*
     * We cannot use 'hostent' as a struct that Curl_resolv() returns.  It
     * returns a Curl_addrinfo pointer that may not always look the same.
     */
    if(dns)
      hp = dns->addr;
    if(hp) {
      char buf[64];
      Curl_printable_address(hp, buf, sizeof(buf));

      if(hp->ai_family == AF_INET) {
        int i;
        struct sockaddr_in *saddr_in;
        socksreq[len++] = 1; /* ATYP: IPv4 = 1 */

        saddr_in = (struct sockaddr_in *)(void *)hp->ai_addr;
        for(i = 0; i < 4; i++) {
          socksreq[len++] = ((unsigned char *)&saddr_in->sin_addr.s_addr)[i];
        }

        infof(data, "SOCKS5 connect to IPv4 %s (locally resolved)\n", buf);
      }
#ifdef ENABLE_IPV6
      else if(hp->ai_family == AF_INET6) {
        int i;
        struct sockaddr_in6 *saddr_in6;
        socksreq[len++] = 4; /* ATYP: IPv6 = 4 */

        saddr_in6 = (struct sockaddr_in6 *)(void *)hp->ai_addr;
        for(i = 0; i < 16; i++) {
          socksreq[len++] =
            ((unsigned char *)&saddr_in6->sin6_addr.s6_addr)[i];
        }

        infof(data, "SOCKS5 connect to IPv6 %s (locally resolved)\n", buf);
      }
#endif
      else {
        hp = NULL; /* fail! */

        failf(data, "SOCKS5 connection to %s not supported\n", buf);
      }

      Curl_resolv_unlock(data, dns); /* not used anymore from now on */
    }
    if(!hp) {
      failf(data, "Failed to resolve \"%s\" for SOCKS5 connect.",
            hostname);
      return CURLE_COULDNT_RESOLVE_HOST;
    }
  }

  socksreq[len++] = (unsigned char)((remote_port >> 8) & 0xff); /* PORT MSB */
  socksreq[len++] = (unsigned char)(remote_port & 0xff);        /* PORT LSB */

#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  if(conn->socks5_gssapi_enctype) {
    failf(data, "SOCKS5 GSS-API protection not yet implemented.");
  }
  else
#endif
    code = Curl_write_plain(conn, sock, (char *)socksreq, len, &written);

  if(code || (len != written)) {
    failf(data, "Failed to send SOCKS5 connect request.");
    return CURLE_COULDNT_CONNECT;
  }

  len = 10; /* minimum packet size is 10 */

#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  if(conn->socks5_gssapi_enctype) {
    failf(data, "SOCKS5 GSS-API protection not yet implemented.");
  }
  else
#endif
    result = Curl_blockread_all(conn, sock, (char *)socksreq,
                                len, &actualread);

  if(result || (len != actualread)) {
    failf(data, "Failed to receive SOCKS5 connect request ack.");
    return CURLE_COULDNT_CONNECT;
  }

  if(socksreq[0] != 5) { /* version */
    failf(data,
          "SOCKS5 reply has wrong version, version should be 5.");
    return CURLE_COULDNT_CONNECT;
  }

  /* Fix: in general, returned BND.ADDR is variable length parameter by RFC
     1928, so the reply packet should be read until the end to avoid errors at
     subsequent protocol level.

    +----+-----+-------+------+----------+----------+
    |VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT |
    +----+-----+-------+------+----------+----------+
    | 1  |  1  | X'00' |  1   | Variable |    2     |
    +----+-----+-------+------+----------+----------+

     ATYP:
     o  IP v4 address: X'01', BND.ADDR = 4 byte
     o  domain name:  X'03', BND.ADDR = [ 1 byte length, string ]
     o  IP v6 address: X'04', BND.ADDR = 16 byte
     */

  /* Calculate real packet size */
  if(socksreq[3] == 3) {
    /* domain name */
    int addrlen = (int) socksreq[4];
    len = 5 + addrlen + 2;
  }
  else if(socksreq[3] == 4) {
    /* IPv6 */
    len = 4 + 16 + 2;
  }

  /* At this point we already read first 10 bytes */
#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  if(!conn->socks5_gssapi_enctype) {
    /* decrypt_gssapi_blockread already read the whole packet */
#endif
    if(len > 10) {
      result = Curl_blockread_all(conn, sock, (char *)&socksreq[10],
                                  len - 10, &actualread);
      if(result || ((len - 10) != actualread)) {
        failf(data, "Failed to receive SOCKS5 connect request ack.");
        return CURLE_COULDNT_CONNECT;
      }
    }
#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  }
#endif

  if(socksreq[1] != 0) { /* Anything besides 0 is an error */
    if(socksreq[3] == 1) {
      failf(data,
            "Can't complete SOCKS5 connection to %d.%d.%d.%d:%d. (%d)",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (((unsigned char)socksreq[8] << 8) |
             (unsigned char)socksreq[9]),
            (unsigned char)socksreq[1]);
    }
    else if(socksreq[3] == 3) {
      unsigned char port_upper = (unsigned char)socksreq[len - 2];
      socksreq[len - 2] = 0;
      failf(data,
            "Can't complete SOCKS5 connection to %s:%d. (%d)",
            (char *)&socksreq[5],
            ((port_upper << 8) |
             (unsigned char)socksreq[len - 1]),
            (unsigned char)socksreq[1]);
      socksreq[len - 2] = port_upper;
    }
    else if(socksreq[3] == 4) {
      failf(data,
            "Can't complete SOCKS5 connection to %02x%02x:%02x%02x:"
            "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%d. (%d)",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (unsigned char)socksreq[8], (unsigned char)socksreq[9],
            (unsigned char)socksreq[10], (unsigned char)socksreq[11],
            (unsigned char)socksreq[12], (unsigned char)socksreq[13],
            (unsigned char)socksreq[14], (unsigned char)socksreq[15],
            (unsigned char)socksreq[16], (unsigned char)socksreq[17],
            (unsigned char)socksreq[18], (unsigned char)socksreq[19],
            (((unsigned char)socksreq[20] << 8) |
             (unsigned char)socksreq[21]),
            (unsigned char)socksreq[1]);
    }
    return CURLE_COULDNT_CONNECT;
  }
  infof(data, "SOCKS5 request granted.\n");

  (void)curlx_nonblock(sock, TRUE);
  return CURLE_OK; /* Proxy was successful! */
}