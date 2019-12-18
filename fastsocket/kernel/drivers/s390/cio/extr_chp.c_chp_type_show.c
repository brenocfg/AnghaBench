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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int desc; } ;
struct channel_path {int /*<<< orphan*/  lock; TYPE_1__ desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct channel_path* to_channelpath (struct device*) ; 

__attribute__((used)) static ssize_t chp_type_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct channel_path *chp = to_channelpath(dev);
	u8 type;

	mutex_lock(&chp->lock);
	type = chp->desc.desc;
	mutex_unlock(&chp->lock);
	return sprintf(buf, "%x\n", type);
}