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

/* Variables and functions */
 unsigned short FRAMERATE_MAX ; 
 int /*<<< orphan*/  FRAMERATE_MIN ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (unsigned short,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned short framerate ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ibmcam_model1_setup_after_video_if(struct uvd *uvd)
{
	unsigned short internal_frame_rate;

	RESTRICT_TO_RANGE(framerate, FRAMERATE_MIN, FRAMERATE_MAX);
	internal_frame_rate = FRAMERATE_MAX - framerate; /* 0=Fast 6=Slow */
	ibmcam_veio(uvd, 0, 0x01, 0x0100);	/* LED On  */
	ibmcam_veio(uvd, 0, internal_frame_rate, 0x0111);
	ibmcam_veio(uvd, 0, 0x01, 0x0114);
	ibmcam_veio(uvd, 0, 0xc0, 0x010c);
}