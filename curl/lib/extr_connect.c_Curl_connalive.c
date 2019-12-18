#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connectdata {scalar_t__* sock; TYPE_1__* ssl; } ;
struct TYPE_2__ {scalar_t__ use; } ;
typedef  int /*<<< orphan*/  RECV_TYPE_ARG4 ;
typedef  int /*<<< orphan*/  RECV_TYPE_ARG3 ;
typedef  int /*<<< orphan*/  RECV_TYPE_ARG2 ;
typedef  int /*<<< orphan*/  RECV_TYPE_ARG1 ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_ssl_check_cxn (struct connectdata*) ; 
 size_t FIRSTSOCKET ; 
 scalar_t__ MSG_PEEK ; 
 scalar_t__ recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool Curl_connalive(struct connectdata *conn)
{
  /* First determine if ssl */
  if(conn->ssl[FIRSTSOCKET].use) {
    /* use the SSL context */
    if(!Curl_ssl_check_cxn(conn))
      return false;   /* FIN received */
  }
/* Minix 3.1 doesn't support any flags on recv; just assume socket is OK */
#ifdef MSG_PEEK
  else if(conn->sock[FIRSTSOCKET] == CURL_SOCKET_BAD)
    return false;
  else {
    /* use the socket */
    char buf;
    if(recv((RECV_TYPE_ARG1)conn->sock[FIRSTSOCKET], (RECV_TYPE_ARG2)&buf,
            (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK) == 0) {
      return false;   /* FIN received */
    }
  }
#endif
  return true;
}