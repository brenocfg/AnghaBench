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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct i2o_device {int dummy; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  opblk ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2O_CMD_UTIL_PARAMS_GET ; 
 int I2O_PARAMS_FIELD_GET ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int i2o_parm_issue (struct i2o_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

int i2o_parm_field_get(struct i2o_device *i2o_dev, int group, int field,
		       void *buf, int buflen)
{
	u32 opblk[] = { cpu_to_le32(0x00000001),
		cpu_to_le32((u16) group << 16 | I2O_PARAMS_FIELD_GET),
		cpu_to_le32((s16) field << 16 | 0x00000001)
	};
	u8 *resblk;		/* 8 bytes for header */
	int rc;

	resblk = kmalloc(buflen + 8, GFP_KERNEL);
	if (!resblk)
		return -ENOMEM;

	rc = i2o_parm_issue(i2o_dev, I2O_CMD_UTIL_PARAMS_GET, opblk,
			    sizeof(opblk), resblk, buflen + 8);

	memcpy(buf, resblk + 8, buflen);	/* cut off header */

	kfree(resblk);

	return rc;
}