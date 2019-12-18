#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {scalar_t__* tempsock; scalar_t__ transport; } ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 scalar_t__ CONNECT_FIRSTSOCKET_PROXY_SSL () ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int Curl_ssl_getsock (struct connectdata*,scalar_t__*) ; 
 int GETSOCK_READSOCK (int) ; 
 int GETSOCK_WRITESOCK (int) ; 
 scalar_t__ TRNSPRT_QUIC ; 

__attribute__((used)) static int waitconnect_getsock(struct connectdata *conn,
                               curl_socket_t *sock)
{
  int i;
  int s = 0;
  int rc = 0;

#ifdef USE_SSL
  if(CONNECT_FIRSTSOCKET_PROXY_SSL())
    return Curl_ssl_getsock(conn, sock);
#endif

  for(i = 0; i<2; i++) {
    if(conn->tempsock[i] != CURL_SOCKET_BAD) {
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s);
#ifdef ENABLE_QUIC
      if(conn->transport == TRNSPRT_QUIC)
        /* when connecting QUIC, we want to read the socket too */
        rc |= GETSOCK_READSOCK(s);
#endif
      s++;
    }
  }

  return rc;
}