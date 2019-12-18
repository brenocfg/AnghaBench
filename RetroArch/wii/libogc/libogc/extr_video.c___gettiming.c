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
typedef  int u32 ;
struct _timing {int dummy; } ;

/* Variables and functions */
#define  VI_TVMODE_EURGB60_DS 139 
#define  VI_TVMODE_EURGB60_INT 138 
#define  VI_TVMODE_EURGB60_PROG 137 
#define  VI_TVMODE_MPAL_DS 136 
#define  VI_TVMODE_MPAL_INT 135 
#define  VI_TVMODE_MPAL_PROG 134 
#define  VI_TVMODE_NTSC_DS 133 
#define  VI_TVMODE_NTSC_INT 132 
#define  VI_TVMODE_NTSC_PROG 131 
#define  VI_TVMODE_PAL_DS 130 
#define  VI_TVMODE_PAL_INT 129 
#define  VI_TVMODE_PAL_PROG 128 
 struct _timing const* video_timing ; 

__attribute__((used)) static const struct _timing* __gettiming(u32 vimode)
{
	switch(vimode) {
		case VI_TVMODE_NTSC_INT:
			return &video_timing[0];
			break;
		case VI_TVMODE_NTSC_DS:
			return &video_timing[1];
			break;
		case VI_TVMODE_PAL_INT:
			return &video_timing[2];
			break;
		case VI_TVMODE_PAL_DS:
			return &video_timing[3];
			break;
		case VI_TVMODE_EURGB60_INT:
			return &video_timing[0];
			break;
		case VI_TVMODE_EURGB60_DS:
			return &video_timing[1];
			break;
		case VI_TVMODE_MPAL_INT:
			return &video_timing[4];
			break;
		case VI_TVMODE_MPAL_DS:
			return &video_timing[5];
			break;
		case VI_TVMODE_NTSC_PROG:
			return &video_timing[6];
			break;
		case VI_TVMODE_PAL_PROG:
			return &video_timing[7];
			break;
		case VI_TVMODE_EURGB60_PROG:
			return &video_timing[6];
			break;
		case VI_TVMODE_MPAL_PROG:
			return &video_timing[6];
			break;
		default:
			return NULL;
	}
}