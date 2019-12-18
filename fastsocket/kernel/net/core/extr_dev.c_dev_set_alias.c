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
struct net_device {int /*<<< orphan*/ * ifalias; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFALIASZ ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krealloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,size_t) ; 

int dev_set_alias(struct net_device *dev, const char *alias, size_t len)
{
	ASSERT_RTNL();

	if (len >= IFALIASZ)
		return -EINVAL;

	if (!len) {
		if (dev->ifalias) {
			kfree(dev->ifalias);
			dev->ifalias = NULL;
		}
		return 0;
	}

	dev->ifalias = krealloc(dev->ifalias, len + 1, GFP_KERNEL);
	if (!dev->ifalias)
		return -ENOMEM;

	strlcpy(dev->ifalias, alias, len+1);
	return len;
}