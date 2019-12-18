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
struct mrvl_meshie_val {int dummy; } ;
struct TYPE_3__ {int mesh_id_len; struct mrvl_meshie* mesh_id; } ;
struct mrvl_meshie {int len; TYPE_1__ val; } ;
struct mrvl_mesh_defaults {char const meshie; } ;
struct lbs_private {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmd_ds_mesh_config {int /*<<< orphan*/  length; int /*<<< orphan*/ * data; } ;
typedef  int ssize_t ;
struct TYPE_4__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_SET ; 
 int /*<<< orphan*/  CMD_TYPE_MESH_SET_MESH_IE ; 
 int EINVAL ; 
 int IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_mesh_config_send (struct lbs_private*,struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mrvl_meshie*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int) ; 
 int mesh_get_default_parameters (struct device*,struct mrvl_mesh_defaults*) ; 
 int strlen (char const*) ; 
 TYPE_2__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t mesh_id_set(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct cmd_ds_mesh_config cmd;
	struct mrvl_mesh_defaults defs;
	struct mrvl_meshie *ie;
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	int len;
	int ret;

	if (count < 2 || count > IW_ESSID_MAX_SIZE + 1)
		return -EINVAL;

	memset(&cmd, 0, sizeof(struct cmd_ds_mesh_config));
	ie = (struct mrvl_meshie *) &cmd.data[0];

	/* fetch all other Information Element parameters */
	ret = mesh_get_default_parameters(dev, &defs);

	cmd.length = cpu_to_le16(sizeof(struct mrvl_meshie));

	/* transfer IE elements */
	memcpy(ie, &defs.meshie, sizeof(struct mrvl_meshie));

	len = count - 1;
	memcpy(ie->val.mesh_id, buf, len);
	/* SSID len */
	ie->val.mesh_id_len = len;
	/* IE len */
	ie->len = sizeof(struct mrvl_meshie_val) - IW_ESSID_MAX_SIZE + len;

	ret = lbs_mesh_config_send(priv, &cmd, CMD_ACT_MESH_CONFIG_SET,
				   CMD_TYPE_MESH_SET_MESH_IE);
	if (ret)
		return ret;

	return strlen(buf);
}