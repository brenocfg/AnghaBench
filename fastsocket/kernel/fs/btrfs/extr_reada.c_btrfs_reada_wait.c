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
struct reada_control {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  elems; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reada_control_release ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int btrfs_reada_wait(void *handle)
{
	struct reada_control *rc = handle;

	while (atomic_read(&rc->elems)) {
		wait_event(rc->wait, atomic_read(&rc->elems) == 0);
	}

	kref_put(&rc->refcnt, reada_control_release);

	return 0;
}