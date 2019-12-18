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
struct fb_videomode {int flag; int vmode; int xres; int yres; int /*<<< orphan*/  refresh; } ;

/* Variables and functions */
 int FB_MODE_IS_DETAILED ; 
 int FB_MODE_IS_STANDARD ; 
 int FB_MODE_IS_VESA ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 scalar_t__ PAGE_SIZE ; 
 int snprintf (char*,scalar_t__,char*,char,int,int,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mode_string(char *buf, unsigned int offset,
		       const struct fb_videomode *mode)
{
	char m = 'U';
	char v = 'p';

	if (mode->flag & FB_MODE_IS_DETAILED)
		m = 'D';
	if (mode->flag & FB_MODE_IS_VESA)
		m = 'V';
	if (mode->flag & FB_MODE_IS_STANDARD)
		m = 'S';

	if (mode->vmode & FB_VMODE_INTERLACED)
		v = 'i';
	if (mode->vmode & FB_VMODE_DOUBLE)
		v = 'd';

	return snprintf(&buf[offset], PAGE_SIZE - offset, "%c:%dx%d%c-%d\n",
	                m, mode->xres, mode->yres, v, mode->refresh);
}