#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket_filter_entry {int sfe_flags; TYPE_2__* sfe_filter; struct socket_filter_entry* sfe_next_onsocket; } ;
typedef  TYPE_3__* socket_t ;
typedef  scalar_t__ sflt_handle ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_7__ {struct socket_filter_entry* so_filt; } ;
struct TYPE_5__ {scalar_t__ sf_handle; } ;
struct TYPE_6__ {TYPE_1__ sf_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SFEF_ATTACHED ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflt_detach_locked (struct socket_filter_entry*) ; 
 int /*<<< orphan*/  sock_filter_lock ; 

errno_t
sflt_detach(socket_t socket, sflt_handle handle)
{
	struct socket_filter_entry *entry;
	errno_t	result = 0;

	if (socket == NULL || handle == 0)
		return (EINVAL);

	lck_rw_lock_exclusive(sock_filter_lock);
	for (entry = socket->so_filt; entry; entry = entry->sfe_next_onsocket) {
		if (entry->sfe_filter->sf_filter.sf_handle == handle &&
		    (entry->sfe_flags & SFEF_ATTACHED) != 0) {
			break;
		}
	}

	if (entry != NULL) {
		sflt_detach_locked(entry);
	}
	lck_rw_unlock_exclusive(sock_filter_lock);

	return (result);
}