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
struct _xy {int dummy; } ;

/* Variables and functions */
 int VIDEO_GetCurrentTvMode () ; 
#define  VI_EURGB60 131 
#define  VI_MPAL 130 
#define  VI_NTSC 129 
#define  VI_PAL 128 
 struct _xy** xy ; 

__attribute__((used)) static __inline__ struct _xy* __si_getxy()
{
	switch(VIDEO_GetCurrentTvMode()) {
		case VI_NTSC:
		case VI_MPAL:
		case VI_EURGB60:
			return xy[0];
			break;
		case VI_PAL:
			return xy[1];
			break;
	}
	return NULL;
}