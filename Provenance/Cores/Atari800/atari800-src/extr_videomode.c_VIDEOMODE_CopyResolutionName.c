#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; int height; } ;

/* Variables and functions */
 TYPE_1__* resolutions ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,int,int) ; 

void VIDEOMODE_CopyResolutionName(unsigned int res_id, char *target, unsigned int size)
{
	snprintf(target, size, "%ix%i", resolutions[res_id].width, resolutions[res_id].height);
}