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
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  hardware_disable_all_nolock () ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 TYPE_2__ kvm_dev ; 
 int /*<<< orphan*/  kvm_lock ; 
 int kvm_usage_count ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void hardware_disable_all(void)
{
	int count;
	char count_string[20];
	char event_string[] = "EVENT=terminate";
	char *envp[] = { event_string, count_string, NULL };

	spin_lock(&kvm_lock);
	hardware_disable_all_nolock();
	count = kvm_usage_count;
	spin_unlock(&kvm_lock);

	sprintf(count_string, "COUNT=%d", count);
	kobject_uevent_env(&kvm_dev.this_device->kobj, KOBJ_CHANGE, envp);
}