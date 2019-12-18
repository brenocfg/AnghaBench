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
typedef  int u32 ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODATA ; 
 scalar_t__ PDCS_ADDR_OSD2 ; 
 scalar_t__ PDC_OK ; 
 scalar_t__ pdc_stable_read (scalar_t__,int*,int) ; 
 int pdcs_size ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t pdcs_osdep2_read(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	char *out = buf;
	unsigned long size;
	unsigned short i;
	u32 result;

	if (unlikely(pdcs_size <= 224))
		return -ENODATA;

	size = pdcs_size - 224;

	if (!buf)
		return -EINVAL;

	for (i=0; i<size; i+=4) {
		if (unlikely(pdc_stable_read(PDCS_ADDR_OSD2 + i, &result,
					sizeof(result)) != PDC_OK))
			return -EIO;
		out += sprintf(out, "0x%.8x\n", result);
	}

	return out - buf;
}