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
struct sockaddr_in6 {int sin6_family; void* sin6_port; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; void* sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_7__ {void* bound; } ;
struct connectdata {long ip_version; TYPE_3__ bits; int /*<<< orphan*/  scope_id; struct Curl_easy* data; } ;
struct Curl_sockaddr_storage {int dummy; } ;
struct TYPE_6__ {int os_errno; void* errorbuf; } ;
struct TYPE_5__ {unsigned short localport; int localportrange; char** str; } ;
struct Curl_easy {TYPE_2__ state; TYPE_1__ set; } ;
struct Curl_dns_entry {TYPE_4__* addr; } ;
typedef  int /*<<< orphan*/  myhost ;
typedef  int curl_socklen_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  add ;
struct TYPE_8__ {int ai_family; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  CURLE_INTERFACE_FAILED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNSUPPORTED_PROTOCOL ; 
 int CURLRESOLV_PENDING ; 
 long CURL_IPRESOLVE_V4 ; 
 long CURL_IPRESOLVE_V6 ; 
 int Curl_if2ip (int,unsigned int,int /*<<< orphan*/ ,char const*,char*,int) ; 
 scalar_t__ Curl_inet_pton (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_printable_address (TYPE_4__*,char*,int) ; 
 int Curl_resolv (struct connectdata*,char const*,int /*<<< orphan*/ ,void*,struct Curl_dns_entry**) ; 
 int /*<<< orphan*/  Curl_resolv_unlock (struct Curl_easy*,struct Curl_dns_entry*) ; 
 int /*<<< orphan*/  Curl_resolver_wait_resolv (struct connectdata*,struct Curl_dns_entry**) ; 
 int /*<<< orphan*/  Curl_strerror (int,char*,int) ; 
 void* FALSE ; 
#define  IF2IP_AF_NOT_SUPPORTED 130 
#define  IF2IP_FOUND 129 
#define  IF2IP_NOT_FOUND 128 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDTODEVICE ; 
 int STRERROR_LEN ; 
 size_t STRING_DEVICE ; 
 void* TRUE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  memset (struct Curl_sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 void* ntohs (unsigned short) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static CURLcode bindlocal(struct connectdata *conn,
                          curl_socket_t sockfd, int af, unsigned int scope)
{
  struct Curl_easy *data = conn->data;

  struct Curl_sockaddr_storage sa;
  struct sockaddr *sock = (struct sockaddr *)&sa;  /* bind to this address */
  curl_socklen_t sizeof_sa = 0; /* size of the data sock points to */
  struct sockaddr_in *si4 = (struct sockaddr_in *)&sa;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *si6 = (struct sockaddr_in6 *)&sa;
#endif

  struct Curl_dns_entry *h = NULL;
  unsigned short port = data->set.localport; /* use this port number, 0 for
                                                "random" */
  /* how many port numbers to try to bind to, increasing one at a time */
  int portnum = data->set.localportrange;
  const char *dev = data->set.str[STRING_DEVICE];
  int error;

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if(!dev && !port)
    /* no local kind of binding was requested */
    return CURLE_OK;

  memset(&sa, 0, sizeof(struct Curl_sockaddr_storage));

  if(dev && (strlen(dev)<255) ) {
    char myhost[256] = "";
    int done = 0; /* -1 for error, 1 for address found */
    bool is_interface = FALSE;
    bool is_host = FALSE;
    static const char *if_prefix = "if!";
    static const char *host_prefix = "host!";

    if(strncmp(if_prefix, dev, strlen(if_prefix)) == 0) {
      dev += strlen(if_prefix);
      is_interface = TRUE;
    }
    else if(strncmp(host_prefix, dev, strlen(host_prefix)) == 0) {
      dev += strlen(host_prefix);
      is_host = TRUE;
    }

    /* interface */
    if(!is_host) {
#ifdef SO_BINDTODEVICE
      /* I am not sure any other OSs than Linux that provide this feature,
       * and at the least I cannot test. --Ben
       *
       * This feature allows one to tightly bind the local socket to a
       * particular interface.  This will force even requests to other
       * local interfaces to go out the external interface.
       *
       *
       * Only bind to the interface when specified as interface, not just
       * as a hostname or ip address.
       *
       * interface might be a VRF, eg: vrf-blue, which means it cannot be
       * converted to an IP address and would fail Curl_if2ip. Simply try
       * to use it straight away.
       */
      if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                    dev, (curl_socklen_t)strlen(dev) + 1) == 0) {
        /* This is typically "errno 1, error: Operation not permitted" if
         * you're not running as root or another suitable privileged
         * user.
         * If it succeeds it means the parameter was a valid interface and
         * not an IP address. Return immediately.
         */
        return CURLE_OK;
      }
#endif

      switch(Curl_if2ip(af, scope, conn->scope_id, dev,
                        myhost, sizeof(myhost))) {
        case IF2IP_NOT_FOUND:
          if(is_interface) {
            /* Do not fall back to treating it as a host name */
            failf(data, "Couldn't bind to interface '%s'", dev);
            return CURLE_INTERFACE_FAILED;
          }
          break;
        case IF2IP_AF_NOT_SUPPORTED:
          /* Signal the caller to try another address family if available */
          return CURLE_UNSUPPORTED_PROTOCOL;
        case IF2IP_FOUND:
          is_interface = TRUE;
          /*
           * We now have the numerical IP address in the 'myhost' buffer
           */
          infof(data, "Local Interface %s is ip %s using address family %i\n",
                dev, myhost, af);
          done = 1;
          break;
      }
    }
    if(!is_interface) {
      /*
       * This was not an interface, resolve the name as a host name
       * or IP number
       *
       * Temporarily force name resolution to use only the address type
       * of the connection. The resolve functions should really be changed
       * to take a type parameter instead.
       */
      long ipver = conn->ip_version;
      int rc;

      if(af == AF_INET)
        conn->ip_version = CURL_IPRESOLVE_V4;
#ifdef ENABLE_IPV6
      else if(af == AF_INET6)
        conn->ip_version = CURL_IPRESOLVE_V6;
#endif

      rc = Curl_resolv(conn, dev, 0, FALSE, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_resolver_wait_resolv(conn, &h);
      conn->ip_version = ipver;

      if(h) {
        /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
        Curl_printable_address(h->addr, myhost, sizeof(myhost));
        infof(data, "Name '%s' family %i resolved to '%s' family %i\n",
              dev, af, myhost, h->addr->ai_family);
        Curl_resolv_unlock(data, h);
        if(af != h->addr->ai_family) {
          /* bad IP version combo, signal the caller to try another address
             family if available */
          return CURLE_UNSUPPORTED_PROTOCOL;
        }
        done = 1;
      }
      else {
        /*
         * provided dev was no interface (or interfaces are not supported
         * e.g. solaris) no ip address and no domain we fail here
         */
        done = -1;
      }
    }

    if(done > 0) {
#ifdef ENABLE_IPV6
      /* IPv6 address */
      if(af == AF_INET6) {
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
        char *scope_ptr = strchr(myhost, '%');
        if(scope_ptr)
          *(scope_ptr++) = 0;
#endif
        if(Curl_inet_pton(AF_INET6, myhost, &si6->sin6_addr) > 0) {
          si6->sin6_family = AF_INET6;
          si6->sin6_port = htons(port);
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
          if(scope_ptr)
            /* The "myhost" string either comes from Curl_if2ip or from
               Curl_printable_address. The latter returns only numeric scope
               IDs and the former returns none at all.  So the scope ID, if
               present, is known to be numeric */
            si6->sin6_scope_id = atoi(scope_ptr);
#endif
        }
        sizeof_sa = sizeof(struct sockaddr_in6);
      }
      else
#endif
      /* IPv4 address */
      if((af == AF_INET) &&
         (Curl_inet_pton(AF_INET, myhost, &si4->sin_addr) > 0)) {
        si4->sin_family = AF_INET;
        si4->sin_port = htons(port);
        sizeof_sa = sizeof(struct sockaddr_in);
      }
    }

    if(done < 1) {
      /* errorbuf is set false so failf will overwrite any message already in
         the error buffer, so the user receives this error message instead of a
         generic resolve error. */
      data->state.errorbuf = FALSE;
      failf(data, "Couldn't bind to '%s'", dev);
      return CURLE_INTERFACE_FAILED;
    }
  }
  else {
    /* no device was given, prepare sa to match af's needs */
#ifdef ENABLE_IPV6
    if(af == AF_INET6) {
      si6->sin6_family = AF_INET6;
      si6->sin6_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in6);
    }
    else
#endif
    if(af == AF_INET) {
      si4->sin_family = AF_INET;
      si4->sin_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in);
    }
  }

  for(;;) {
    if(bind(sockfd, sock, sizeof_sa) >= 0) {
      /* we succeeded to bind */
      struct Curl_sockaddr_storage add;
      curl_socklen_t size = sizeof(add);
      memset(&add, 0, sizeof(struct Curl_sockaddr_storage));
      if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {
        char buffer[STRERROR_LEN];
        data->state.os_errno = error = SOCKERRNO;
        failf(data, "getsockname() failed with errno %d: %s",
              error, Curl_strerror(error, buffer, sizeof(buffer)));
        return CURLE_INTERFACE_FAILED;
      }
      infof(data, "Local port: %hu\n", port);
      conn->bits.bound = TRUE;
      return CURLE_OK;
    }

    if(--portnum > 0) {
      infof(data, "Bind to local port %hu failed, trying next\n", port);
      port++; /* try next port */
      /* We re-use/clobber the port variable here below */
      if(sock->sa_family == AF_INET)
        si4->sin_port = ntohs(port);
#ifdef ENABLE_IPV6
      else
        si6->sin6_port = ntohs(port);
#endif
    }
    else
      break;
  }
  {
    char buffer[STRERROR_LEN];
    data->state.os_errno = error = SOCKERRNO;
    failf(data, "bind failed with errno %d: %s",
          error, Curl_strerror(error, buffer, sizeof(buffer)));
  }

  return CURLE_INTERFACE_FAILED;
}