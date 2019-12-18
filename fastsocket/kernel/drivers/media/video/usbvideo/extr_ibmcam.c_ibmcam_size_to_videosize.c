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
typedef  int /*<<< orphan*/  videosize_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int /*<<< orphan*/ ,scalar_t__) ; 
#define  SIZE_128x96 134 
#define  SIZE_160x120 133 
#define  SIZE_176x144 132 
#define  SIZE_320x240 131 
#define  SIZE_352x240 130 
#define  SIZE_352x288 129 
#define  SIZE_640x480 128 
 scalar_t__ SIZE_LastItem ; 
 int /*<<< orphan*/  VIDEOSIZE_128x96 ; 
 int /*<<< orphan*/  VIDEOSIZE_160x120 ; 
 int /*<<< orphan*/  VIDEOSIZE_176x144 ; 
 int /*<<< orphan*/  VIDEOSIZE_320x240 ; 
 int /*<<< orphan*/  VIDEOSIZE_352x240 ; 
 int /*<<< orphan*/  VIDEOSIZE_352x288 ; 
 int /*<<< orphan*/  VIDEOSIZE_640x480 ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static videosize_t ibmcam_size_to_videosize(int size)
{
	videosize_t vs = VIDEOSIZE_352x288;
	RESTRICT_TO_RANGE(size, 0, (SIZE_LastItem-1));
	switch (size) {
	case SIZE_128x96:
		vs = VIDEOSIZE_128x96;
		break;
	case SIZE_160x120:
		vs = VIDEOSIZE_160x120;
		break;
	case SIZE_176x144:
		vs = VIDEOSIZE_176x144;
		break;
	case SIZE_320x240:
		vs = VIDEOSIZE_320x240;
		break;
	case SIZE_352x240:
		vs = VIDEOSIZE_352x240;
		break;
	case SIZE_352x288:
		vs = VIDEOSIZE_352x288;
		break;
	case SIZE_640x480:
		vs = VIDEOSIZE_640x480;
		break;
	default:
		err("size=%d. is not valid", size);
		break;
	}
	return vs;
}