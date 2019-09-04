#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct TYPE_4__ {int sb_idealsize; } ;
struct socket {scalar_t__ so_type; TYPE_3__* so_msg_state; TYPE_1__ so_snd; } ;
struct mbuf {int dummy; } ;
struct TYPE_6__ {TYPE_2__* msg_priq; } ;
struct TYPE_5__ {int msgq_bytes; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 size_t MSG_PRI_0 ; 
 int MSG_PRI_COUNT ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int tcp_get_msg_priority (struct mbuf*,size_t*) ; 

int
msgq_sbspace(struct socket *so, struct mbuf *control)
{
	int space = 0, error;
	u_int32_t msgpri = 0;
	VERIFY(so->so_type == SOCK_STREAM &&
		SOCK_PROTO(so) == IPPROTO_TCP);
	if (control != NULL) {
		error = tcp_get_msg_priority(control, &msgpri);
		if (error)
			return (0);
	} else {
		msgpri = MSG_PRI_0;
	}
	space = (so->so_snd.sb_idealsize / MSG_PRI_COUNT) -
	    so->so_msg_state->msg_priq[msgpri].msgq_bytes;
	if (space < 0)
		space = 0;
	return (space);
}