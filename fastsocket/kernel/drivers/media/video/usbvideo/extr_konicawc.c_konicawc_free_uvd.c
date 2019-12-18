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
struct uvd {scalar_t__ user_data; } ;
struct konicawc {int /*<<< orphan*/ ** sts_urb; } ;

/* Variables and functions */
 int USBVIDEO_NUMSBUF ; 
 int /*<<< orphan*/  konicawc_unregister_input (struct konicawc*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void konicawc_free_uvd(struct uvd *uvd)
{
	int i;
	struct konicawc *cam = (struct konicawc *)uvd->user_data;

	konicawc_unregister_input(cam);

	for (i = 0; i < USBVIDEO_NUMSBUF; i++) {
		usb_free_urb(cam->sts_urb[i]);
		cam->sts_urb[i] = NULL;
	}
}