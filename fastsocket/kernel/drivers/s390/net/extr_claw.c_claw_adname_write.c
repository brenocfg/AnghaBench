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
struct claw_env {int* adapter_name; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int*) ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 int MAX_NAME_LEN ; 
 struct claw_privbk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  strncpy (int*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
claw_adname_write(struct device *dev, struct device_attribute *attr,
	 const char *buf, size_t count)
{
	struct claw_privbk *priv;
	struct claw_env *  p_env;

	priv = dev_get_drvdata(dev);
	if (!priv)
		return -ENODEV;
	p_env = priv->p_env;
	if (count > MAX_NAME_LEN+1)
		return -EINVAL;
	memset(p_env->adapter_name, 0x20, MAX_NAME_LEN);
	strncpy(p_env->adapter_name,buf, count);
	p_env->adapter_name[count-1] = 0x20; /* clear extra 0x0a */
	p_env->adapter_name[MAX_NAME_LEN] = 0x00;
	CLAW_DBF_TEXT(2, setup, "AdnSet");
	CLAW_DBF_TEXT_(2, setup, "%s", p_env->adapter_name);

	return count;
}