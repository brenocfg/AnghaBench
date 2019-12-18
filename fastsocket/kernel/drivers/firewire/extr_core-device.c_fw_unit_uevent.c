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
struct fw_unit {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  modalias ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,char*) ; 
 struct fw_unit* fw_unit (struct device*) ; 
 int /*<<< orphan*/  get_modalias (struct fw_unit*,char*,int) ; 

__attribute__((used)) static int fw_unit_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct fw_unit *unit = fw_unit(dev);
	char modalias[64];

	get_modalias(unit, modalias, sizeof(modalias));

	if (add_uevent_var(env, "MODALIAS=%s", modalias))
		return -ENOMEM;

	return 0;
}