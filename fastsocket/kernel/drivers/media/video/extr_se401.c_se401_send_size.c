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
struct usb_se401 {int sizes; int* width; int* height; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_BAYER ; 
 int /*<<< orphan*/  FMT_JANGGU ; 
 int /*<<< orphan*/  SE401_OPERATINGMODE ; 
 int /*<<< orphan*/  SE401_REQ_SET_HEIGHT ; 
 int /*<<< orphan*/  SE401_REQ_SET_WIDTH ; 
 int /*<<< orphan*/  se401_set_feature (struct usb_se401*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_sndctrl (int,struct usb_se401*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void se401_send_size(struct usb_se401 *se401, int width, int height)
{
	int i = 0;
	int mode = 0x03; /* No compression */
	int sendheight = height;
	int sendwidth = width;

	/* JangGu compression can only be used with the camera supported sizes,
	   but bayer seems to work with any size that fits on the sensor.
	   We check if we can use compression with the current size with either
	   4 or 16 times subcapturing, if not we use uncompressed bayer data
	   but this will result in cutouts of the maximum size....
	 */
	while (i < se401->sizes && !(se401->width[i] == width &&
						se401->height[i] == height))
		i++;
	while (i < se401->sizes) {
		if (se401->width[i] == width * 2 &&
				se401->height[i] == height * 2) {
			sendheight = se401->height[i];
			sendwidth = se401->width[i];
			mode = 0x40;
		}
		if (se401->width[i] == width * 4 &&
				se401->height[i] == height * 4) {
			sendheight = se401->height[i];
			sendwidth = se401->width[i];
			mode = 0x42;
		}
		i++;
	}

	se401_sndctrl(1, se401, SE401_REQ_SET_WIDTH, sendwidth, NULL, 0);
	se401_sndctrl(1, se401, SE401_REQ_SET_HEIGHT, sendheight, NULL, 0);
	se401_set_feature(se401, SE401_OPERATINGMODE, mode);

	if (mode == 0x03)
		se401->format = FMT_BAYER;
	else
		se401->format = FMT_JANGGU;
}