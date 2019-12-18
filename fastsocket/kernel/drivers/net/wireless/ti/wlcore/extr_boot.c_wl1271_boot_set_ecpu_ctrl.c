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
typedef  int /*<<< orphan*/  u32 ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ECPU_CONTROL ; 
 int wlcore_read_reg (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wlcore_write_reg (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1271_boot_set_ecpu_ctrl(struct wl1271 *wl, u32 flag)
{
	u32 cpu_ctrl;
	int ret;

	/* 10.5.0 run the firmware (I) */
	ret = wlcore_read_reg(wl, REG_ECPU_CONTROL, &cpu_ctrl);
	if (ret < 0)
		goto out;

	/* 10.5.1 run the firmware (II) */
	cpu_ctrl |= flag;
	ret = wlcore_write_reg(wl, REG_ECPU_CONTROL, cpu_ctrl);

out:
	return ret;
}