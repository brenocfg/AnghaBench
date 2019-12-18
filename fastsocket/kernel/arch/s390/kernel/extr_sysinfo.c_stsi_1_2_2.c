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
struct sysinfo_1_2_2_extension {int alt_capability; int* alt_adjustment; } ;
struct sysinfo_1_2_2 {int cpus_total; int cpus_configured; int cpus_standby; int cpus_reserved; int format; int capability; int* adjustment; int secondary_capability; scalar_t__ acc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stsi (struct sysinfo_1_2_2*,int,int,int) ; 

__attribute__((used)) static int stsi_1_2_2(struct sysinfo_1_2_2 *info, char *page, int len)
{
	struct sysinfo_1_2_2_extension *ext;
	int i;

	if (stsi(info, 1, 2, 2) == -ENOSYS)
		return len;
	ext = (struct sysinfo_1_2_2_extension *)
		((unsigned long) info + info->acc_offset);

	len += sprintf(page + len, "\n");
	len += sprintf(page + len, "CPUs Total:           %d\n",
		       info->cpus_total);
	len += sprintf(page + len, "CPUs Configured:      %d\n",
		       info->cpus_configured);
	len += sprintf(page + len, "CPUs Standby:         %d\n",
		       info->cpus_standby);
	len += sprintf(page + len, "CPUs Reserved:        %d\n",
		       info->cpus_reserved);

	if (info->format == 1) {
		/*
		 * Sigh 2. According to the specification the alternate
		 * capability field is a 32 bit floating point number
		 * if the higher order 8 bits are not zero. Printing
		 * a floating point number in the kernel is a no-no,
		 * always print the number as 32 bit unsigned integer.
		 * The user-space needs to know about the strange
		 * encoding of the alternate cpu capability.
		 */
		len += sprintf(page + len, "Capability:           %u %u\n",
			       info->capability, ext->alt_capability);
		for (i = 2; i <= info->cpus_total; i++)
			len += sprintf(page + len,
				       "Adjustment %02d-way:    %u %u\n",
				       i, info->adjustment[i-2],
				       ext->alt_adjustment[i-2]);

	} else {
		len += sprintf(page + len, "Capability:           %u\n",
			       info->capability);
		for (i = 2; i <= info->cpus_total; i++)
			len += sprintf(page + len,
				       "Adjustment %02d-way:    %u\n",
				       i, info->adjustment[i-2]);
	}

	if (info->secondary_capability != 0)
		len += sprintf(page + len, "Secondary Capability: %d\n",
			       info->secondary_capability);
	return len;
}