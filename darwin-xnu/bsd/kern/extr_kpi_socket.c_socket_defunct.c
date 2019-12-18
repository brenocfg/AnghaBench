#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct proc {int dummy; } ;
typedef  TYPE_3__* socket_t ;
typedef  scalar_t__ errno_t ;
struct TYPE_10__ {int sb_flags; } ;
struct TYPE_9__ {int sb_flags; } ;
struct TYPE_11__ {TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EOPNOTSUPP ; 
 int SB_UNIX ; 
 int SHUTDOWN_SOCKET_LEVEL_DISCONNECT_ALL ; 
 int SHUTDOWN_SOCKET_LEVEL_DISCONNECT_SVC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  socket_lock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_3__*,int) ; 
 scalar_t__ sodefunct (struct proc*,TYPE_3__*,int) ; 
 scalar_t__ sosetdefunct (struct proc*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 

errno_t
socket_defunct(struct proc *p, socket_t so, int level)
{
	errno_t retval;

	if (level != SHUTDOWN_SOCKET_LEVEL_DISCONNECT_SVC &&
	    level != SHUTDOWN_SOCKET_LEVEL_DISCONNECT_ALL)
		return (EINVAL);

	socket_lock(so, 1);
	/*
	 * SHUTDOWN_SOCKET_LEVEL_DISCONNECT_SVC level is meant to tear down
	 * all of mDNSResponder IPC sockets, currently those of AF_UNIX; note
	 * that this is an implementation artifact of mDNSResponder.  We do
	 * a quick test against the socket buffers for SB_UNIX, since that
	 * would have been set by unp_attach() at socket creation time.
	 */
	if (level == SHUTDOWN_SOCKET_LEVEL_DISCONNECT_SVC &&
	    (so->so_rcv.sb_flags & so->so_snd.sb_flags & SB_UNIX) != SB_UNIX) {
		socket_unlock(so, 1);
		return (EOPNOTSUPP);
	}
	retval = sosetdefunct(p, so, level, TRUE);
	if (retval == 0)
		retval = sodefunct(p, so, level);
	socket_unlock(so, 1);
	return (retval);
}