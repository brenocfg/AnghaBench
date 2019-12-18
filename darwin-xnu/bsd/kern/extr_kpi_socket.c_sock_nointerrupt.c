#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* socket_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_9__ {TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_NOINTR ; 
 int /*<<< orphan*/  socket_lock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_3__*,int) ; 

errno_t
sock_nointerrupt(socket_t sock, int on)
{
	socket_lock(sock, 1);

	if (on) {
		sock->so_rcv.sb_flags |= SB_NOINTR;	/* This isn't safe */
		sock->so_snd.sb_flags |= SB_NOINTR;	/* This isn't safe */
	} else {
		sock->so_rcv.sb_flags &= ~SB_NOINTR;	/* This isn't safe */
		sock->so_snd.sb_flags &= ~SB_NOINTR;	/* This isn't safe */
	}

	socket_unlock(sock, 1);

	return (0);
}