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
typedef  int /*<<< orphan*/  u8 ;
struct regulatory_request {int /*<<< orphan*/  alpha2; int /*<<< orphan*/  processed; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int reg_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct regulatory_request *lr;
	u8 alpha2[2];
	bool add = false;

	rcu_read_lock();
	lr = get_last_request();
	if (lr && !lr->processed) {
		memcpy(alpha2, lr->alpha2, 2);
		add = true;
	}
	rcu_read_unlock();

	if (add)
		return add_uevent_var(env, "COUNTRY=%c%c",
				      alpha2[0], alpha2[1]);
	return 0;
}