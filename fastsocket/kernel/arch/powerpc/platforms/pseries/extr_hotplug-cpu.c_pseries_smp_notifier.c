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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
#define  PSERIES_RECONFIG_ADD 129 
#define  PSERIES_RECONFIG_REMOVE 128 
 int /*<<< orphan*/  pseries_add_processor (void*) ; 
 int /*<<< orphan*/  pseries_remove_processor (void*) ; 

__attribute__((used)) static int pseries_smp_notifier(struct notifier_block *nb,
				unsigned long action, void *node)
{
	int err = NOTIFY_OK;

	switch (action) {
	case PSERIES_RECONFIG_ADD:
		if (pseries_add_processor(node))
			err = NOTIFY_BAD;
		break;
	case PSERIES_RECONFIG_REMOVE:
		pseries_remove_processor(node);
		break;
	default:
		err = NOTIFY_DONE;
		break;
	}
	return err;
}