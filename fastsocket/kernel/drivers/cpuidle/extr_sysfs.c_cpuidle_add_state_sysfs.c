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
struct cpuidle_state_kobj {int /*<<< orphan*/  kobj; int /*<<< orphan*/  kobj_unregister; int /*<<< orphan*/ * state; } ;
struct cpuidle_device {int state_count; struct cpuidle_state_kobj** kobjs; int /*<<< orphan*/  kobj; int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  cpuidle_free_state_kobj (struct cpuidle_device*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuidle_state_kobj*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_state_cpuidle ; 
 struct cpuidle_state_kobj* kzalloc (int,int /*<<< orphan*/ ) ; 

int cpuidle_add_state_sysfs(struct cpuidle_device *device)
{
	int i, ret = -ENOMEM;
	struct cpuidle_state_kobj *kobj;

	/* state statistics */
	for (i = 0; i < device->state_count; i++) {
		kobj = kzalloc(sizeof(struct cpuidle_state_kobj), GFP_KERNEL);
		if (!kobj)
			goto error_state;
		kobj->state = &device->states[i];
		init_completion(&kobj->kobj_unregister);

		ret = kobject_init_and_add(&kobj->kobj, &ktype_state_cpuidle, &device->kobj,
					   "state%d", i);
		if (ret) {
			kfree(kobj);
			goto error_state;
		}
		kobject_uevent(&kobj->kobj, KOBJ_ADD);
		device->kobjs[i] = kobj;
	}

	return 0;

error_state:
	for (i = i - 1; i >= 0; i--)
		cpuidle_free_state_kobj(device, i);
	return ret;
}