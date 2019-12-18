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
struct socket {int so_flags; scalar_t__ so_usecount; int /*<<< orphan*/ * so_cfil; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfs_sock_detached; } ;

/* Variables and functions */
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int SOF_CONTENT_FILTER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cfil_db_free (struct socket*) ; 
 int /*<<< orphan*/  cfil_info_free (int /*<<< orphan*/ *) ; 
 TYPE_1__ cfil_stats ; 

errno_t
cfil_sock_detach(struct socket *so)
{
	if (IS_UDP(so)) {
		cfil_db_free(so);
		return (0);
	}

	if (so->so_cfil) {
		if (so->so_flags & SOF_CONTENT_FILTER) {
			so->so_flags &= ~SOF_CONTENT_FILTER;
			VERIFY(so->so_usecount > 0);
			so->so_usecount--;
		}
		cfil_info_free(so->so_cfil);
		so->so_cfil = NULL;
		OSIncrementAtomic(&cfil_stats.cfs_sock_detached);
	}
	return (0);
}