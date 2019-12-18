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
struct usb_stv {int streaming; int vwidth; int vheight; int maxwidth; int maxheight; int QVGA; int CIF; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int,char*,int,int,...) ; 
 int /*<<< orphan*/  stv680_start_stream (struct usb_stv*) ; 
 int /*<<< orphan*/  stv680_stop_stream (struct usb_stv*) ; 

__attribute__((used)) static int stv680_set_size (struct usb_stv *stv680, int width, int height)
{
	int wasstreaming = stv680->streaming;

	/* Check to see if we need to change */
	if ((stv680->vwidth == width) && (stv680->vheight == height))
		return 0;

	PDEBUG (1, "STV(i): size request for %i x %i", width, height);
	/* Check for a valid mode */
	if ((!width || !height) || ((width & 1) || (height & 1))) {
		PDEBUG (1, "STV(e): set_size error: request: v.width = %i, v.height = %i  actual: stv.width = %i, stv.height = %i", width, height, stv680->vwidth, stv680->vheight);
		return 1;
	}

	if ((width < (stv680->maxwidth / 2)) || (height < (stv680->maxheight / 2))) {
		width = stv680->maxwidth / 2;
		height = stv680->maxheight / 2;
	} else if ((width >= 158) && (width <= 166) && (stv680->QVGA == 1)) {
		width = 160;
		height = 120;
	} else if ((width >= 172) && (width <= 180) && (stv680->CIF == 1)) {
		width = 176;
		height = 144;
	} else if ((width >= 318) && (width <= 350) && (stv680->QVGA == 1)) {
		width = 320;
		height = 240;
	} else if ((width >= 350) && (width <= 358) && (stv680->CIF == 1)) {
		width = 352;
		height = 288;
	} else {
		PDEBUG (1, "STV(e): request for non-supported size: request: v.width = %i, v.height = %i  actual: stv.width = %i, stv.height = %i", width, height, stv680->vwidth, stv680->vheight);
		return 1;
	}

	/* Stop a current stream and start it again at the new size */
	if (wasstreaming)
		stv680_stop_stream (stv680);
	stv680->vwidth = width;
	stv680->vheight = height;
	PDEBUG (1, "STV(i): size set to %i x %i", stv680->vwidth, stv680->vheight);
	if (wasstreaming)
		stv680_start_stream (stv680);

	return 0;
}