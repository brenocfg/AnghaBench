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
typedef  int /*<<< orphan*/  u8 ;
struct socket {int dummy; } ;
struct rfcomm_session {struct socket* sock; } ;
struct msghdr {int dummy; } ;
struct kvec {int member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int) ; 
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,int,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfcomm_send_frame(struct rfcomm_session *s, u8 *data, int len)
{
	struct socket *sock = s->sock;
	struct kvec iv = { data, len };
	struct msghdr msg;

	BT_DBG("session %p len %d", s, len);

	memset(&msg, 0, sizeof(msg));

	return kernel_sendmsg(sock, &msg, &iv, 1, len);
}