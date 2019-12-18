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
struct TYPE_4__ {int window_type; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_INPUT_MODE_REG ; 
 int /*<<< orphan*/  HWA742_TRANSL_MODE_REG1 ; 
 int /*<<< orphan*/  HWA742_WINDOW_TYPE ; 
 int OMAPFB_FORMAT_FLAG_DOUBLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ hwa742 ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_format_regs(int conv, int transl, int flags)
{
	if (flags & OMAPFB_FORMAT_FLAG_DOUBLE) {
		hwa742.window_type = ((hwa742.window_type & 0xfc) | 0x01);
#ifdef VERBOSE
		dev_dbg(hwa742.fbdev->dev, "hwa742: enabled pixel doubling\n");
#endif
	} else {
		hwa742.window_type = (hwa742.window_type & 0xfc);
#ifdef VERBOSE
		dev_dbg(hwa742.fbdev->dev, "hwa742: disabled pixel doubling\n");
#endif
	}

	hwa742_write_reg(HWA742_INPUT_MODE_REG, conv);
	hwa742_write_reg(HWA742_TRANSL_MODE_REG1, transl);
	hwa742_write_reg(HWA742_WINDOW_TYPE, hwa742.window_type);
}