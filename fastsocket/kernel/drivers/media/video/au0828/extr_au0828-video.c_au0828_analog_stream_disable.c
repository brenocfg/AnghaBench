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
 int /*<<< orphan*/  AU0828_SENSORCTRL_100 ; 
 int /*<<< orphan*/  au0828_writereg (struct au0828_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

int au0828_analog_stream_disable(struct au0828_dev *d)
{
	dprintk(1, "au0828_analog_stream_disable called\n");
	au0828_writereg(d, AU0828_SENSORCTRL_100, 0x0);
	return 0;
}