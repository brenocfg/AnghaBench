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
struct claw_env {int write_buffers; scalar_t__ packing; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int) ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 struct claw_privbk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t
claw_wbuff_write(struct device *dev, struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct claw_privbk *priv;
	struct claw_env *  p_env;
	int nnn,max;

	priv = dev_get_drvdata(dev);
	if (!priv)
		return -ENODEV;
	p_env = priv->p_env;
	sscanf(buf, "%i", &nnn);
	if (p_env->packing) {
		max = 64;
	}
	else {
		max = 512;
	}
	if ((nnn > max ) || (nnn < 2))
		return -EINVAL;
	p_env->write_buffers = nnn;
	CLAW_DBF_TEXT(2, setup, "Wbufset");
	CLAW_DBF_TEXT_(2, setup, "WB=%d", p_env->write_buffers);
	return count;
}