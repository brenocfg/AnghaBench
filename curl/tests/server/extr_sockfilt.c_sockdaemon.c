#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int sin_family; int sin6_family; int sa_family; void* sin6_port; void* sin_port; int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;
struct TYPE_7__ {TYPE_3__ sa6; TYPE_3__ sa4; TYPE_3__ sa; } ;
typedef  TYPE_2__ srvr_sockaddr_union_t ;
typedef  int /*<<< orphan*/  flag ;
typedef  int curl_socklen_t ;
typedef  unsigned short curl_socket_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned short CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int bind (unsigned short,TYPE_3__*,int) ; 
 scalar_t__ bind_only ; 
 int errno ; 
 scalar_t__ getsockname (unsigned short,TYPE_3__*,int*) ; 
 scalar_t__ got_exit_signal ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int listen (unsigned short,int) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 unsigned short ntohs (void*) ; 
 int /*<<< orphan*/  sclose (unsigned short) ; 
 int setsockopt (unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  use_ipv6 ; 
 int wait_ms (int) ; 

__attribute__((used)) static curl_socket_t sockdaemon(curl_socket_t sock,
                                unsigned short *listenport)
{
  /* passive daemon style */
  srvr_sockaddr_union_t listener;
  int flag;
  int rc;
  int totdelay = 0;
  int maxretr = 10;
  int delay = 20;
  int attempt = 0;
  int error = 0;

  do {
    attempt++;
    flag = 1;
    rc = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
         (void *)&flag, sizeof(flag));
    if(rc) {
      error = SOCKERRNO;
      logmsg("setsockopt(SO_REUSEADDR) failed with error: (%d) %s",
             error, strerror(error));
      if(maxretr) {
        rc = wait_ms(delay);
        if(rc) {
          /* should not happen */
          error = errno;
          logmsg("wait_ms() failed with error: (%d) %s",
                 error, strerror(error));
          sclose(sock);
          return CURL_SOCKET_BAD;
        }
        if(got_exit_signal) {
          logmsg("signalled to die, exiting...");
          sclose(sock);
          return CURL_SOCKET_BAD;
        }
        totdelay += delay;
        delay *= 2; /* double the sleep for next attempt */
      }
    }
  } while(rc && maxretr--);

  if(rc) {
    logmsg("setsockopt(SO_REUSEADDR) failed %d times in %d ms. Error: (%d) %s",
           attempt, totdelay, error, strerror(error));
    logmsg("Continuing anyway...");
  }

  /* When the specified listener port is zero, it is actually a
     request to let the system choose a non-zero available port. */

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    memset(&listener.sa4, 0, sizeof(listener.sa4));
    listener.sa4.sin_family = AF_INET;
    listener.sa4.sin_addr.s_addr = INADDR_ANY;
    listener.sa4.sin_port = htons(*listenport);
    rc = bind(sock, &listener.sa, sizeof(listener.sa4));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&listener.sa6, 0, sizeof(listener.sa6));
    listener.sa6.sin6_family = AF_INET6;
    listener.sa6.sin6_addr = in6addr_any;
    listener.sa6.sin6_port = htons(*listenport);
    rc = bind(sock, &listener.sa, sizeof(listener.sa6));
  }
#endif /* ENABLE_IPV6 */
  if(rc) {
    error = SOCKERRNO;
    logmsg("Error binding socket on port %hu: (%d) %s",
           *listenport, error, strerror(error));
    sclose(sock);
    return CURL_SOCKET_BAD;
  }

  if(!*listenport) {
    /* The system was supposed to choose a port number, figure out which
       port we actually got and update the listener port value with it. */
    curl_socklen_t la_size;
    srvr_sockaddr_union_t localaddr;
#ifdef ENABLE_IPV6
    if(!use_ipv6)
#endif
      la_size = sizeof(localaddr.sa4);
#ifdef ENABLE_IPV6
    else
      la_size = sizeof(localaddr.sa6);
#endif
    memset(&localaddr.sa, 0, (size_t)la_size);
    if(getsockname(sock, &localaddr.sa, &la_size) < 0) {
      error = SOCKERRNO;
      logmsg("getsockname() failed with error: (%d) %s",
             error, strerror(error));
      sclose(sock);
      return CURL_SOCKET_BAD;
    }
    switch(localaddr.sa.sa_family) {
    case AF_INET:
      *listenport = ntohs(localaddr.sa4.sin_port);
      break;
#ifdef ENABLE_IPV6
    case AF_INET6:
      *listenport = ntohs(localaddr.sa6.sin6_port);
      break;
#endif
    default:
      break;
    }
    if(!*listenport) {
      /* Real failure, listener port shall not be zero beyond this point. */
      logmsg("Apparently getsockname() succeeded, with listener port zero.");
      logmsg("A valid reason for this failure is a binary built without");
      logmsg("proper network library linkage. This might not be the only");
      logmsg("reason, but double check it before anything else.");
      sclose(sock);
      return CURL_SOCKET_BAD;
    }
  }

  /* bindonly option forces no listening */
  if(bind_only) {
    logmsg("instructed to bind port without listening");
    return sock;
  }

  /* start accepting connections */
  rc = listen(sock, 5);
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("listen(%d, 5) failed with error: (%d) %s",
           sock, error, strerror(error));
    sclose(sock);
    return CURL_SOCKET_BAD;
  }

  return sock;
}