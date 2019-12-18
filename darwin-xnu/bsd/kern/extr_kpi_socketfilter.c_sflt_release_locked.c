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
struct TYPE_2__ {int /*<<< orphan*/  sf_handle; int /*<<< orphan*/  (* sf_unregistered ) (int /*<<< orphan*/ ) ;} ;
struct socket_filter {scalar_t__ sf_refcount; TYPE_1__ sf_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct socket_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_filter_lock ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sflt_release_locked(struct socket_filter *filter)
{
	filter->sf_refcount--;
	if (filter->sf_refcount == 0) {
		/* Call the unregistered function */
		if (filter->sf_filter.sf_unregistered) {
			lck_rw_unlock_exclusive(sock_filter_lock);
			filter->sf_filter.sf_unregistered(
			    filter->sf_filter.sf_handle);
			lck_rw_lock_exclusive(sock_filter_lock);
		}

		/* Free the entry */
		FREE(filter, M_IFADDR);
	}
}