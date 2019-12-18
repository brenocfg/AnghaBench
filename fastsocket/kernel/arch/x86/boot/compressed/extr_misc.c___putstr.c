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
struct TYPE_3__ {scalar_t__ orig_video_mode; int orig_x; int orig_y; } ;
struct TYPE_4__ {TYPE_1__ screen_info; } ;

/* Variables and functions */
 int cols ; 
 int lines ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_2__* real_mode ; 
 int /*<<< orphan*/  scroll () ; 
 char* vidmem ; 
 scalar_t__ vidport ; 

__attribute__((used)) static void __putstr(int error, const char *s)
{
	int x, y, pos;
	char c;

#ifndef CONFIG_X86_VERBOSE_BOOTUP
	if (!error)
		return;
#endif

#ifdef CONFIG_X86_32
	if (real_mode->screen_info.orig_video_mode == 0 &&
	    lines == 0 && cols == 0)
		return;
#endif

	x = real_mode->screen_info.orig_x;
	y = real_mode->screen_info.orig_y;

	while ((c = *s++) != '\0') {
		if (c == '\n') {
			x = 0;
			if (++y >= lines) {
				scroll();
				y--;
			}
		} else {
			vidmem[(x + cols * y) * 2] = c;
			if (++x >= cols) {
				x = 0;
				if (++y >= lines) {
					scroll();
					y--;
				}
			}
		}
	}

	real_mode->screen_info.orig_x = x;
	real_mode->screen_info.orig_y = y;

	pos = (x + cols * y) * 2;	/* Update cursor position */
	outb(14, vidport);
	outb(0xff & (pos >> 9), vidport+1);
	outb(15, vidport);
	outb(0xff & (pos >> 1), vidport+1);
}