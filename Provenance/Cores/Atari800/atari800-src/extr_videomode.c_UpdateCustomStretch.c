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
#define  VIDEOMODE_STRETCH_2X 132 
#define  VIDEOMODE_STRETCH_3X 131 
#define  VIDEOMODE_STRETCH_FULL 130 
#define  VIDEOMODE_STRETCH_INTEGER 129 
#define  VIDEOMODE_STRETCH_NONE 128 
 double VIDEOMODE_custom_stretch ; 
 int VIDEOMODE_stretch ; 

__attribute__((used)) static void UpdateCustomStretch(void)
{
	switch (VIDEOMODE_stretch) {
	case VIDEOMODE_STRETCH_NONE:
	case VIDEOMODE_STRETCH_2X:
	case VIDEOMODE_STRETCH_3X:
		VIDEOMODE_custom_stretch = (double)(VIDEOMODE_stretch + 1);
		break;
	case VIDEOMODE_STRETCH_INTEGER:
	case VIDEOMODE_STRETCH_FULL:
		VIDEOMODE_custom_stretch = 1.0;
		break;
	}
}