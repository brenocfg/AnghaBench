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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct claw_privbk {struct claw_env* p_env; } ;
struct claw_env {int write_buffers; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct claw_privbk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
claw_wbuff_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct claw_privbk *priv;
	struct claw_env * p_env;

	priv = dev_get_drvdata(dev);
	if (!priv)
		return -ENODEV;
	p_env = priv->p_env;
	return sprintf(buf, "%d\n", p_env->write_buffers);
}