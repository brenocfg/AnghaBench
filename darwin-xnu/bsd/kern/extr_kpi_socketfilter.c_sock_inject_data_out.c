#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  TYPE_1__* socket_t ;
typedef  int sflt_data_flag_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int so_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int MSG_OOB ; 
 int SOF_MP_SUBFLOW ; 
 int sock_data_filt_flag_oob ; 
 int /*<<< orphan*/  sosend (TYPE_1__*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

errno_t
sock_inject_data_out(socket_t so, const struct sockaddr *to, mbuf_t data,
    mbuf_t control, sflt_data_flag_t flags)
{
	int sosendflags = 0;

	/* reject if this is a subflow socket */
	if (so->so_flags & SOF_MP_SUBFLOW)
		return (ENOTSUP);

	if (flags & sock_data_filt_flag_oob)
		sosendflags = MSG_OOB;
	return (sosend(so, (struct sockaddr *)(uintptr_t)to, NULL,
	    data, control, sosendflags));
}