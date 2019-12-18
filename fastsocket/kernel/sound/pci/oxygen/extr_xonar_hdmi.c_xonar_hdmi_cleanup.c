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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_write_command (struct oxygen*,int,int,int /*<<< orphan*/ *) ; 

void xonar_hdmi_cleanup(struct oxygen *chip)
{
	u8 param = 0;

	hdmi_write_command(chip, 0x74, 1, &param);
}