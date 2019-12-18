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
struct mipid_device {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ls041y3_esd_check_mode1 (struct mipid_device*) ; 
 int /*<<< orphan*/  ls041y3_esd_check_mode2 (struct mipid_device*) ; 

__attribute__((used)) static void ls041y3_esd_check(struct mipid_device *md)
{
	ls041y3_esd_check_mode1(md);
	if (md->revision >= 0x88)
		ls041y3_esd_check_mode2(md);
}