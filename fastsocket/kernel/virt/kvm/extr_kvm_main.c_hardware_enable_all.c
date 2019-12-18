#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* this_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_disable_all_nolock () ; 
 int /*<<< orphan*/  hardware_enable ; 
 int /*<<< orphan*/  hardware_enable_failed ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 TYPE_2__ kvm_dev ; 
 int /*<<< orphan*/  kvm_lock ; 
 int kvm_usage_count ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int hardware_enable_all(void)
{
	int r = 0;
	int count;

	spin_lock(&kvm_lock);

	count = ++kvm_usage_count;
	if (kvm_usage_count == 1) {
		atomic_set(&hardware_enable_failed, 0);
		on_each_cpu(hardware_enable, NULL, 1);

		if (atomic_read(&hardware_enable_failed)) {
			hardware_disable_all_nolock();
			r = -EBUSY;
		}
	}

	spin_unlock(&kvm_lock);

	if (r == 0) {
		char count_string[20];
		char event_string[] = "EVENT=create";
		char *envp[] = { event_string, count_string, NULL };

		sprintf(count_string, "COUNT=%d", count);
		kobject_uevent_env(&kvm_dev.this_device->kobj, KOBJ_CHANGE, envp);
	}
	return r;
}