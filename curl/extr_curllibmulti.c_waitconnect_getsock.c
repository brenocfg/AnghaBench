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
struct connectdata {scalar_t__* tempsock; } ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int GETSOCK_BLANK ; 
 int GETSOCK_WRITESOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waitconnect_getsock(struct connectdata *conn,
                               curl_socket_t *sock,
                               int numsocks)
{
  int i;
  int s = 0;
  int rc = 0;

  if(!numsocks)
    return GETSOCK_BLANK;

#ifdef USE_SSL
  if(CONNECT_FIRSTSOCKET_PROXY_SSL())
    return Curl_ssl_getsock(conn, sock, numsocks);
#endif

  for(i = 0; i<2; i++) {
    if(conn->tempsock[i] != CURL_SOCKET_BAD) {
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s++);
    }
  }

  return rc;
}