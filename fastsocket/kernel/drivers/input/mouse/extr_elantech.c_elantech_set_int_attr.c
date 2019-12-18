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
struct psmouse {struct elantech_data* private; } ;
struct elantech_data {int hw_version; } ;
struct elantech_attr_data {int field_offset; int reg; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long ETP_R10_ABSOLUTE_MODE ; 
 unsigned long ETP_R11_4_BYTE_MODE ; 
 scalar_t__ elantech_write_reg (struct psmouse*,int,unsigned long) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t elantech_set_int_attr(struct psmouse *psmouse,
				     void *data, const char *buf, size_t count)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_attr_data *attr = data;
	unsigned char *reg = (unsigned char *) etd + attr->field_offset;
	unsigned long value;
	int err;

	err = strict_strtoul(buf, 16, &value);
	if (err)
		return err;

	if (value > 0xff)
		return -EINVAL;

	/* Do we need to preserve some bits for version 2 hardware too? */
	if (etd->hw_version == 1) {
		if (attr->reg == 0x10)
			/* Force absolute mode always on */
			value |= ETP_R10_ABSOLUTE_MODE;
		else if (attr->reg == 0x11)
			/* Force 4 byte mode always on */
			value |= ETP_R11_4_BYTE_MODE;
	}

	if (!attr->reg || elantech_write_reg(psmouse, attr->reg, value) == 0)
		*reg = value;

	return count;
}