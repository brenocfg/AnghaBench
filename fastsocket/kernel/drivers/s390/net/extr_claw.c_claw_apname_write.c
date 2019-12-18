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
struct claw_env {int* api_type; void* write_size; void* read_size; scalar_t__ packing; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int*) ; 
 void* CLAW_FRAME_SIZE ; 
 void* DEF_PACK_BUFSIZE ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 int MAX_NAME_LEN ; 
 scalar_t__ PACKING_ASK ; 
 int /*<<< orphan*/  WS_APPL_NAME_PACKED ; 
 struct claw_privbk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  setup ; 
 scalar_t__ strncmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
claw_apname_write(struct device *dev, struct device_attribute *attr,
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
	memset(p_env->api_type, 0x20, MAX_NAME_LEN);
	strncpy(p_env->api_type,buf, count);
	p_env->api_type[count-1] = 0x20;  /* we get a loose 0x0a */
	p_env->api_type[MAX_NAME_LEN] = 0x00;
	if(strncmp(p_env->api_type,WS_APPL_NAME_PACKED,6) == 0) {
		p_env->read_size=DEF_PACK_BUFSIZE;
		p_env->write_size=DEF_PACK_BUFSIZE;
		p_env->packing=PACKING_ASK;
		CLAW_DBF_TEXT(2, setup, "PACKING");
	}
	else {
		p_env->packing=0;
		p_env->read_size=CLAW_FRAME_SIZE;
		p_env->write_size=CLAW_FRAME_SIZE;
		CLAW_DBF_TEXT(2, setup, "ApiSet");
	}
	CLAW_DBF_TEXT_(2, setup, "%s", p_env->api_type);
	return count;
}