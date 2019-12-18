#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int slice_type; } ;
typedef  TYPE_1__ H264SliceContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  AV_PICTURE_TYPE_B 132 
#define  AV_PICTURE_TYPE_I 131 
#define  AV_PICTURE_TYPE_P 130 
#define  AV_PICTURE_TYPE_SI 129 
#define  AV_PICTURE_TYPE_SP 128 

int ff_h264_get_slice_type(const H264SliceContext *sl)
{
    switch (sl->slice_type) {
    case AV_PICTURE_TYPE_P:
        return 0;
    case AV_PICTURE_TYPE_B:
        return 1;
    case AV_PICTURE_TYPE_I:
        return 2;
    case AV_PICTURE_TYPE_SP:
        return 3;
    case AV_PICTURE_TYPE_SI:
        return 4;
    default:
        return AVERROR_INVALIDDATA;
    }
}