#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct of_device {TYPE_1__* node; } ;
struct kobj_uevent_env {int buflen; int /*<<< orphan*/ * buf; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,...) ; 
 int of_device_get_modalias (struct of_device*,int /*<<< orphan*/ *,int) ; 
 char* of_get_property (TYPE_1__*,char*,int*) ; 
 int strlen (char const*) ; 
 struct of_device* to_of_device (struct device*) ; 

int of_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct of_device *ofdev;
	const char *compat;
	int seen = 0, cplen, sl;

	if (!dev)
		return -ENODEV;

	ofdev = to_of_device(dev);

	if (add_uevent_var(env, "OF_NAME=%s", ofdev->node->name))
		return -ENOMEM;

	if (add_uevent_var(env, "OF_TYPE=%s", ofdev->node->type))
		return -ENOMEM;

        /* Since the compatible field can contain pretty much anything
         * it's not really legal to split it out with commas. We split it
         * up using a number of environment variables instead. */

	compat = of_get_property(ofdev->node, "compatible", &cplen);
	while (compat && *compat && cplen > 0) {
		if (add_uevent_var(env, "OF_COMPATIBLE_%d=%s", seen, compat))
			return -ENOMEM;

		sl = strlen (compat) + 1;
		compat += sl;
		cplen -= sl;
		seen++;
	}

	if (add_uevent_var(env, "OF_COMPATIBLE_N=%d", seen))
		return -ENOMEM;

	/* modalias is trickier, we add it in 2 steps */
	if (add_uevent_var(env, "MODALIAS="))
		return -ENOMEM;
	sl = of_device_get_modalias(ofdev, &env->buf[env->buflen-1],
				    sizeof(env->buf) - env->buflen);
	if (sl >= (sizeof(env->buf) - env->buflen))
		return -ENOMEM;
	env->buflen += sl;

	return 0;
}