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
typedef  enum AVColorRange { ____Placeholder_AVColorRange } AVColorRange ;

/* Variables and functions */
#define  AVCOL_RANGE_JPEG 130 
#define  AVCOL_RANGE_MPEG 129 
#define  AVCOL_RANGE_UNSPECIFIED 128 
 int ZIMG_RANGE_FULL ; 
 int ZIMG_RANGE_LIMITED ; 

__attribute__((used)) static int convert_range(enum AVColorRange color_range)
{
    switch (color_range) {
    case AVCOL_RANGE_UNSPECIFIED:
    case AVCOL_RANGE_MPEG:
        return ZIMG_RANGE_LIMITED;
    case AVCOL_RANGE_JPEG:
        return ZIMG_RANGE_FULL;
    }
    return ZIMG_RANGE_LIMITED;
}