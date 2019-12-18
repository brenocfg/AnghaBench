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
struct uvd {int dummy; } ;
struct usbvideo_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbvideo_OverlayChar (struct uvd*,struct usbvideo_frame*,int,int,char const) ; 

__attribute__((used)) static void usbvideo_OverlayString(struct uvd *uvd, struct usbvideo_frame *frame,
				   int x, int y, const char *str)
{
	while (*str) {
		usbvideo_OverlayChar(uvd, frame, x, y, *str);
		str++;
		x += 4; /* 3 pixels character + 1 space */
	}
}