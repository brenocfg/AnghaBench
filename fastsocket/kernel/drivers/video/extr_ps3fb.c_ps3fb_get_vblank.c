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
struct fb_vblank {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VBLANK_HAVE_VSYNC ; 
 int /*<<< orphan*/  memset (struct fb_vblank*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ps3fb_get_vblank(struct fb_vblank *vblank)
{
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VSYNC;
	return 0;
}