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
struct lbs_private {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cmd_ds_mesh_access {void** data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mesh_access ;
struct TYPE_2__ {struct lbs_private* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT ; 
 unsigned long CMD_ACT_SET ; 
 int ENOTSUPP ; 
 void* cpu_to_le32 (unsigned long) ; 
 int lbs_mesh_access (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_mesh_access*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_mesh_access*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strict_strtoul (char const*,int,unsigned long*) ; 
 int strlen (char const*) ; 
 TYPE_1__* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t lbs_prb_rsp_limit_set(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct lbs_private *priv = to_net_dev(dev)->ml_priv;
	struct cmd_ds_mesh_access mesh_access;
	int ret;
	unsigned long retry_limit;

	memset(&mesh_access, 0, sizeof(mesh_access));
	mesh_access.data[0] = cpu_to_le32(CMD_ACT_SET);

	if (!strict_strtoul(buf, 10, &retry_limit))
		return -ENOTSUPP;
	if (retry_limit > 15)
		return -ENOTSUPP;

	mesh_access.data[1] = cpu_to_le32(retry_limit);

	ret = lbs_mesh_access(priv, CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT,
			&mesh_access);
	if (ret)
		return ret;

	return strlen(buf);
}