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
struct connectdata {int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 size_t FIRSTSOCKET ; 
 int GETSOCK_WRITESOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsp_getsock_do(struct connectdata *conn,
                           curl_socket_t *socks)
{
  /* write mode */
  socks[0] = conn->sock[FIRSTSOCKET];
  return GETSOCK_WRITESOCK(0);
}