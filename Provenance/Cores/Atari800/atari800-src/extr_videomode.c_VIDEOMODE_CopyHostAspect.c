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

/* Variables and functions */
 double VIDEOMODE_host_aspect_ratio_h ; 
 double VIDEOMODE_host_aspect_ratio_w ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,double,double) ; 

void VIDEOMODE_CopyHostAspect(char *target, unsigned int size)
{
	snprintf(target, size, "%g:%g", VIDEOMODE_host_aspect_ratio_w, VIDEOMODE_host_aspect_ratio_h);
}