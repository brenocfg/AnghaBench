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
struct au0828_dev {int dummy; } ;

/* Variables and functions */
 int AU0828_SENSORCTRL_100 ; 
 int AU0828_SENSORCTRL_VBI_103 ; 
 int /*<<< orphan*/  au0828_writereg (struct au0828_dev*,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

int au0828_analog_stream_enable(struct au0828_dev *d)
{
	dprintk(1, "au0828_analog_stream_enable called\n");
	au0828_writereg(d, AU0828_SENSORCTRL_VBI_103, 0x00);
	au0828_writereg(d, 0x106, 0x00);
	/* set x position */
	au0828_writereg(d, 0x110, 0x00);
	au0828_writereg(d, 0x111, 0x00);
	au0828_writereg(d, 0x114, 0xa0);
	au0828_writereg(d, 0x115, 0x05);
	/* set y position */
	au0828_writereg(d, 0x112, 0x00);
	au0828_writereg(d, 0x113, 0x00);
	au0828_writereg(d, 0x116, 0xf2);
	au0828_writereg(d, 0x117, 0x00);
	au0828_writereg(d, AU0828_SENSORCTRL_100, 0xb3);

	return 0;
}