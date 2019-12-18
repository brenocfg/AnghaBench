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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct sa1100fb_info {int palette_size; int* palette_cpu; TYPE_1__ fb; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int palette_pbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sa1100fb_setpalettereg(u_int regno, u_int red, u_int green, u_int blue,
		       u_int trans, struct fb_info *info)
{
	struct sa1100fb_info *fbi = (struct sa1100fb_info *)info;
	u_int val, ret = 1;

	if (regno < fbi->palette_size) {
		val = ((red >> 4) & 0xf00);
		val |= ((green >> 8) & 0x0f0);
		val |= ((blue >> 12) & 0x00f);

		if (regno == 0)
			val |= palette_pbs(&fbi->fb.var);

		fbi->palette_cpu[regno] = val;
		ret = 0;
	}
	return ret;
}