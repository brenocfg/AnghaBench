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
 int /*<<< orphan*/  ibmcam_adjust_contrast (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_set_brightness (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_set_hue (struct uvd*) ; 

__attribute__((used)) static void ibmcam_adjust_picture(struct uvd *uvd)
{
	ibmcam_adjust_contrast(uvd);
	ibmcam_set_brightness(uvd);
	ibmcam_set_hue(uvd);
}