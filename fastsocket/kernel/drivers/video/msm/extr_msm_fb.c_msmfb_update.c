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
typedef  int /*<<< orphan*/  uint32_t ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msmfb_pan_update (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msmfb_update(struct fb_info *info, uint32_t left, uint32_t top,
			 uint32_t eright, uint32_t ebottom)
{
	msmfb_pan_update(info, left, top, eright, ebottom, 0, 0);
}