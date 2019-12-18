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
struct TYPE_2__ {int length; } ;
struct fb_var_screeninfo {TYPE_1__ green; } ;

/* Variables and functions */

__attribute__((used)) static int riva_get_cmap_len(const struct fb_var_screeninfo *var)
{
	int rc = 256;		/* reasonable default */

	switch (var->green.length) {
	case 8:
		rc = 256;	/* 256 entries (2^8), 8 bpp and RGB8888 */
		break;
	case 5:
		rc = 32;	/* 32 entries (2^5), 16 bpp, RGB555 */
		break;
	case 6:
		rc = 64;	/* 64 entries (2^6), 16 bpp, RGB565 */
		break;		
	default:
		/* should not occur */
		break;
	}
	return rc;
}