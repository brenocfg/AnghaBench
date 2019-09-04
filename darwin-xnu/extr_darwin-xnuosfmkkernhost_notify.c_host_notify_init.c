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
struct host_notify_entry {int dummy; } ;

/* Variables and functions */
 int HOST_NOTIFY_TYPE_MAX ; 
 int /*<<< orphan*/  host_notify_lock ; 
 int /*<<< orphan*/  host_notify_lock_attr ; 
 int /*<<< orphan*/  host_notify_lock_ext ; 
 int /*<<< orphan*/  host_notify_lock_grp ; 
 int /*<<< orphan*/  host_notify_lock_grp_attr ; 
 int /*<<< orphan*/ * host_notify_queue ; 
 int /*<<< orphan*/  host_notify_zone ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zinit (int,int,int,char*) ; 

void
host_notify_init(void)
{
	int		i;

	for (i = 0; i <= HOST_NOTIFY_TYPE_MAX; i++)
		queue_init(&host_notify_queue[i]);

	lck_grp_attr_setdefault(&host_notify_lock_grp_attr);
	lck_grp_init(&host_notify_lock_grp, "host_notify", &host_notify_lock_grp_attr);
	lck_attr_setdefault(&host_notify_lock_attr);

	lck_mtx_init_ext(&host_notify_lock, &host_notify_lock_ext, &host_notify_lock_grp, &host_notify_lock_attr);

	i = sizeof (struct host_notify_entry);
	host_notify_zone =
			zinit(i, (4096 * i), (16 * i), "host_notify");
}