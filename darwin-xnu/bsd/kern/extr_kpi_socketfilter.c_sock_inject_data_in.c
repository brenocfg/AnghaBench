#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  TYPE_1__* socket_t ;
typedef  int sflt_data_flag_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int errno_t ;
struct TYPE_6__ {int so_flags; int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int SOF_MP_SUBFLOW ; 
 scalar_t__ sbappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sbappendcontrol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sbappendrecord (int /*<<< orphan*/ *,struct mbuf*) ; 
 int sock_data_filt_flag_oob ; 
 int sock_data_filt_flag_record ; 
 int /*<<< orphan*/  socket_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sorwakeup (TYPE_1__*) ; 

errno_t
sock_inject_data_in(socket_t so, const struct sockaddr *from, mbuf_t data,
    mbuf_t control, sflt_data_flag_t flags)
{
	int error = 0;

	if (so == NULL || data == NULL)
		return (EINVAL);

	if (flags & sock_data_filt_flag_oob) {
		return (ENOTSUP);
	}

	socket_lock(so, 1);

	/* reject if this is a subflow socket */
	if (so->so_flags & SOF_MP_SUBFLOW) {
		error = ENOTSUP;
		goto done;
	}

	if (from) {
		if (sbappendaddr(&so->so_rcv,
		    (struct sockaddr *)(uintptr_t)from, data, control, NULL))
			sorwakeup(so);
		goto done;
	}

	if (control) {
		if (sbappendcontrol(&so->so_rcv, data, control, NULL))
			sorwakeup(so);
		goto done;
	}

	if (flags & sock_data_filt_flag_record) {
		if (control || from) {
			error = EINVAL;
			goto done;
		}
		if (sbappendrecord(&so->so_rcv, (struct mbuf *)data))
			sorwakeup(so);
		goto done;
	}

	if (sbappend(&so->so_rcv, data))
		sorwakeup(so);
done:
	socket_unlock(so, 1);
	return (error);
}