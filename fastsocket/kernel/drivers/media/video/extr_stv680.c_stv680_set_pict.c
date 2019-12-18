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
struct video_picture {scalar_t__ palette; scalar_t__ brightness; int /*<<< orphan*/  depth; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  colour; int /*<<< orphan*/  whiteness; } ;
struct usb_stv {scalar_t__ brightness; int chgbright; scalar_t__ palette; int /*<<< orphan*/  depth; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  colour; int /*<<< orphan*/  whiteness; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 scalar_t__ STV_VIDEO_PALETTE ; 

__attribute__((used)) static int stv680_set_pict (struct usb_stv *stv680, struct video_picture *p)
{
	/* See above stv680_get_pict  */

	if (p->palette != STV_VIDEO_PALETTE) {
		PDEBUG (2, "STV(e): Palette set error in _set_pic");
		return 1;
	}

	if (stv680->brightness != p->brightness) {
		stv680->chgbright = 1;
		stv680->brightness = p->brightness;
	}

	stv680->whiteness = p->whiteness;	/* greyscale */
	stv680->colour = p->colour;
	stv680->contrast = p->contrast;
	stv680->hue = p->hue;
	stv680->palette = p->palette;
	stv680->depth = p->depth;

	return 0;
}