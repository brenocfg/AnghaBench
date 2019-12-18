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
struct video_picture {int /*<<< orphan*/  depth; int /*<<< orphan*/  palette; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  colour; int /*<<< orphan*/  whiteness; int /*<<< orphan*/  brightness; } ;
struct usb_stv {int /*<<< orphan*/  depth; int /*<<< orphan*/  palette; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  colour; int /*<<< orphan*/  whiteness; int /*<<< orphan*/  brightness; } ;

/* Variables and functions */

__attribute__((used)) static int stv680_get_pict (struct usb_stv *stv680, struct video_picture *p)
{
	/* This sets values for v4l interface. max/min = 65535/0  */

	p->brightness = stv680->brightness;
	p->whiteness = stv680->whiteness;	/* greyscale */
	p->colour = stv680->colour;
	p->contrast = stv680->contrast;
	p->hue = stv680->hue;
	p->palette = stv680->palette;
	p->depth = stv680->depth;
	return 0;
}