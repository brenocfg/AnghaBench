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
struct video_picture {scalar_t__ palette; int hue; scalar_t__ brightness; int whiteness; } ;
struct usb_se401 {scalar_t__ palette; int hue; int rgain; int bgain; scalar_t__ brightness; int enhance; } ;

/* Variables and functions */
 scalar_t__ VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  se401_send_pict (struct usb_se401*) ; 
 int /*<<< orphan*/  se401_set_exposure (struct usb_se401*,scalar_t__) ; 

__attribute__((used)) static int se401_set_pict(struct usb_se401 *se401, struct video_picture *p)
{
	if (p->palette != VIDEO_PALETTE_RGB24)
		return 1;
	se401->palette = p->palette;
	if (p->hue != se401->hue) {
		se401->rgain =  p->hue >> 10;
		se401->bgain =  0x40-(p->hue >> 10);
		se401->hue = p->hue;
	}
	if (p->brightness != se401->brightness)
		se401_set_exposure(se401, p->brightness);

	if (p->whiteness >= 32768)
		se401->enhance = 1;
	else
		se401->enhance = 0;
	se401_send_pict(se401);
	se401_send_pict(se401);
	return 0;
}