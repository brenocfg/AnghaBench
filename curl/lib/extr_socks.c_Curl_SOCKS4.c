#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct TYPE_7__ {scalar_t__ httpproxy; } ;
struct TYPE_6__ {scalar_t__ proxytype; } ;
struct connectdata {struct Curl_easy* data; TYPE_2__ bits; int /*<<< orphan*/ * sock; TYPE_1__ socks_proxy; } ;
struct Curl_easy {int dummy; } ;
struct Curl_dns_entry {TYPE_4__* addr; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socksreq ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {scalar_t__ ai_family; scalar_t__ ai_addr; } ;
typedef  TYPE_4__ Curl_addrinfo ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  CURLE_COULDNT_CONNECT ; 
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_HOST ; 
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_PROXY ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OPERATION_TIMEDOUT ; 
 scalar_t__ CURLPROXY_SOCKS4A ; 
 int CURLRESOLV_ERROR ; 
 int CURLRESOLV_PENDING ; 
 int Curl_blockread_all (struct connectdata*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  Curl_printable_address (TYPE_4__*,char*,int) ; 
 int Curl_resolv (struct connectdata*,char const*,int,int,struct Curl_dns_entry**) ; 
 int /*<<< orphan*/  Curl_resolv_unlock (struct Curl_easy*,struct Curl_dns_entry*) ; 
 int /*<<< orphan*/  Curl_resolver_wait_resolv (struct connectdata*,struct Curl_dns_entry**) ; 
 scalar_t__ Curl_timeleft (struct Curl_easy*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Curl_write_plain (struct connectdata*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int FALSE ; 
 int SOCKS4REQLEN ; 
 int TRUE ; 
 int /*<<< orphan*/  curlx_nonblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char const*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 void* strlen (char const*) ; 

CURLcode Curl_SOCKS4(const char *proxy_user,
                     const char *hostname,
                     int remote_port,
                     int sockindex,
                     struct connectdata *conn)
{
  const bool protocol4a =
    (conn->socks_proxy.proxytype == CURLPROXY_SOCKS4A) ? TRUE : FALSE;
#define SOCKS4REQLEN 262
  unsigned char socksreq[SOCKS4REQLEN]; /* room for SOCKS4 request incl. user
                                           id */
  CURLcode code;
  curl_socket_t sock = conn->sock[sockindex];
  struct Curl_easy *data = conn->data;

  if(Curl_timeleft(data, NULL, TRUE) < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(conn->bits.httpproxy)
    infof(conn->data, "SOCKS4%s: connecting to HTTP proxy %s port %d\n",
          protocol4a ? "a" : "", hostname, remote_port);

  (void)curlx_nonblock(sock, FALSE);

  infof(data, "SOCKS4 communication to %s:%d\n", hostname, remote_port);

  /*
   * Compose socks4 request
   *
   * Request format
   *
   *     +----+----+----+----+----+----+----+----+----+----+....+----+
   *     | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
   *     +----+----+----+----+----+----+----+----+----+----+....+----+
   * # of bytes:  1    1      2              4           variable       1
   */

  socksreq[0] = 4; /* version (SOCKS4) */
  socksreq[1] = 1; /* connect */
  socksreq[2] = (unsigned char)((remote_port >> 8) & 0xff); /* PORT MSB */
  socksreq[3] = (unsigned char)(remote_port & 0xff);        /* PORT LSB */

  /* DNS resolve only for SOCKS4, not SOCKS4a */
  if(!protocol4a) {
    struct Curl_dns_entry *dns;
    Curl_addrinfo *hp = NULL;
    int rc;

    rc = Curl_resolv(conn, hostname, remote_port, FALSE, &dns);

    if(rc == CURLRESOLV_ERROR)
      return CURLE_COULDNT_RESOLVE_PROXY;

    if(rc == CURLRESOLV_PENDING)
      /* ignores the return code, but 'dns' remains NULL on failure */
      (void)Curl_resolver_wait_resolv(conn, &dns);

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
        struct sockaddr_in *saddr_in;

        saddr_in = (struct sockaddr_in *)(void *)hp->ai_addr;
        socksreq[4] = ((unsigned char *)&saddr_in->sin_addr.s_addr)[0];
        socksreq[5] = ((unsigned char *)&saddr_in->sin_addr.s_addr)[1];
        socksreq[6] = ((unsigned char *)&saddr_in->sin_addr.s_addr)[2];
        socksreq[7] = ((unsigned char *)&saddr_in->sin_addr.s_addr)[3];

        infof(data, "SOCKS4 connect to IPv4 %s (locally resolved)\n", buf);
      }
      else {
        hp = NULL; /* fail! */

        failf(data, "SOCKS4 connection to %s not supported\n", buf);
      }

      Curl_resolv_unlock(data, dns); /* not used anymore from now on */
    }
    if(!hp) {
      failf(data, "Failed to resolve \"%s\" for SOCKS4 connect.",
            hostname);
      return CURLE_COULDNT_RESOLVE_HOST;
    }
  }

  /*
   * This is currently not supporting "Identification Protocol (RFC1413)".
   */
  socksreq[8] = 0; /* ensure empty userid is NUL-terminated */
  if(proxy_user) {
    size_t plen = strlen(proxy_user);
    if(plen >= sizeof(socksreq) - 8) {
      failf(data, "Too long SOCKS proxy name, can't use!\n");
      return CURLE_COULDNT_CONNECT;
    }
    /* copy the proxy name WITH trailing zero */
    memcpy(socksreq + 8, proxy_user, plen + 1);
  }

  /*
   * Make connection
   */
  {
    int result;
    ssize_t actualread;
    ssize_t written;
    ssize_t hostnamelen = 0;
    ssize_t packetsize = 9 +
      strlen((char *)socksreq + 8); /* size including NUL */

    /* If SOCKS4a, set special invalid IP address 0.0.0.x */
    if(protocol4a) {
      socksreq[4] = 0;
      socksreq[5] = 0;
      socksreq[6] = 0;
      socksreq[7] = 1;
      /* If still enough room in buffer, also append hostname */
      hostnamelen = (ssize_t)strlen(hostname) + 1; /* length including NUL */
      if(packetsize + hostnamelen <= SOCKS4REQLEN)
        strcpy((char *)socksreq + packetsize, hostname);
      else
        hostnamelen = 0; /* Flag: hostname did not fit in buffer */
    }

    /* Send request */
    code = Curl_write_plain(conn, sock, (char *)socksreq,
                            packetsize + hostnamelen,
                            &written);
    if(code || (written != packetsize + hostnamelen)) {
      failf(data, "Failed to send SOCKS4 connect request.");
      return CURLE_COULDNT_CONNECT;
    }
    if(protocol4a && hostnamelen == 0) {
      /* SOCKS4a with very long hostname - send that name separately */
      hostnamelen = (ssize_t)strlen(hostname) + 1;
      code = Curl_write_plain(conn, sock, (char *)hostname, hostnamelen,
                              &written);
      if(code || (written != hostnamelen)) {
        failf(data, "Failed to send SOCKS4 connect request.");
        return CURLE_COULDNT_CONNECT;
      }
    }

    packetsize = 8; /* receive data size */

    /* Receive response */
    result = Curl_blockread_all(conn, sock, (char *)socksreq, packetsize,
                                &actualread);
    if(result || (actualread != packetsize)) {
      failf(data, "Failed to receive SOCKS4 connect request ack.");
      return CURLE_COULDNT_CONNECT;
    }

    /*
     * Response format
     *
     *     +----+----+----+----+----+----+----+----+
     *     | VN | CD | DSTPORT |      DSTIP        |
     *     +----+----+----+----+----+----+----+----+
     * # of bytes:  1    1      2              4
     *
     * VN is the version of the reply code and should be 0. CD is the result
     * code with one of the following values:
     *
     * 90: request granted
     * 91: request rejected or failed
     * 92: request rejected because SOCKS server cannot connect to
     *     identd on the client
     * 93: request rejected because the client program and identd
     *     report different user-ids
     */

    /* wrong version ? */
    if(socksreq[0] != 0) {
      failf(data,
            "SOCKS4 reply has wrong version, version should be 0.");
      return CURLE_COULDNT_CONNECT;
    }

    /* Result */
    switch(socksreq[1]) {
    case 90:
      infof(data, "SOCKS4%s request granted.\n", protocol4a?"a":"");
      break;
    case 91:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected or failed.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (((unsigned char)socksreq[2] << 8) | (unsigned char)socksreq[3]),
            (unsigned char)socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    case 92:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected because SOCKS server cannot connect to "
            "identd on the client.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (((unsigned char)socksreq[2] << 8) | (unsigned char)socksreq[3]),
            (unsigned char)socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    case 93:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", request rejected because the client program and identd "
            "report different user-ids.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (((unsigned char)socksreq[2] << 8) | (unsigned char)socksreq[3]),
            (unsigned char)socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    default:
      failf(data,
            "Can't complete SOCKS4 connection to %d.%d.%d.%d:%d. (%d)"
            ", Unknown.",
            (unsigned char)socksreq[4], (unsigned char)socksreq[5],
            (unsigned char)socksreq[6], (unsigned char)socksreq[7],
            (((unsigned char)socksreq[2] << 8) | (unsigned char)socksreq[3]),
            (unsigned char)socksreq[1]);
      return CURLE_COULDNT_CONNECT;
    }
  }

  (void)curlx_nonblock(sock, TRUE);

  return CURLE_OK; /* Proxy was successful! */
}