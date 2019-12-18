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
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cpu_modalias (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cpuid_dev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	char *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (buf) {
		print_cpu_modalias(NULL, NULL, buf);
		add_uevent_var(env, "MODALIAS=%s", buf);
		kfree(buf);
	}
	return 0;
}