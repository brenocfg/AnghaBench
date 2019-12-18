#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int mesh_capability; } ;
struct mrvl_meshie {TYPE_1__ val; } ;
struct mrvl_mesh_defaults {int /*<<< orphan*/  meshie; } ;
struct lbs_private {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmd_ds_mesh_config {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_SET ; 
 int /*<<< orphan*/  CMD_TYPE_MESH_SET_MESH_IE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_mesh_config_send (struct lbs_private*,struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mrvl_meshie*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int) ; 
 int mesh_get_default_parameters (struct device*,struct mrvl_mesh_defaults*) ; 
 int sscanf (char const*,char*,int*) ; 
 int strlen (char const*) ; 
 TYPE_2__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t capability_set(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct cmd_ds_mesh_config cmd;
	struct mrvl_mesh_defaults defs;
	struct mrvl_meshie *ie;
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	uint32_t datum;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	ret = sscanf(buf, "%d", &datum);
	if ((ret != 1) || (datum > 255))
		return -EINVAL;

	/* fetch all other Information Element parameters */
	ret = mesh_get_default_parameters(dev, &defs);

	cmd.length = cpu_to_le16(sizeof(struct mrvl_meshie));

	/* transfer IE elements */
	ie = (struct mrvl_meshie *) &cmd.data[0];
	memcpy(ie, &defs.meshie, sizeof(struct mrvl_meshie));
	/* update value */
	ie->val.mesh_capability = datum;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (ret)
		return ret;

	return strlen(buf);
}