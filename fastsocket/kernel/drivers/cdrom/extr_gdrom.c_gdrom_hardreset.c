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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDROM_RESET_REG ; 
 int /*<<< orphan*/  ctrl_inl (int) ; 
 int /*<<< orphan*/  ctrl_outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdrom_hardreset(struct cdrom_device_info *cd_info)
{
	int count;
	ctrl_outl(0x1fffff, GDROM_RESET_REG);
	for (count = 0xa0000000; count < 0xa0200000; count += 4)
		ctrl_inl(count);
	return 0;
}