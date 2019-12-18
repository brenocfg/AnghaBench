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
struct firmware_priv {int /*<<< orphan*/  fw_id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct firmware_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  loading_timeout ; 

__attribute__((used)) static int firmware_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct firmware_priv *fw_priv = dev_get_drvdata(dev);

	if (add_uevent_var(env, "FIRMWARE=%s", fw_priv->fw_id))
		return -ENOMEM;
	if (add_uevent_var(env, "TIMEOUT=%i", loading_timeout))
		return -ENOMEM;

	return 0;
}