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
#define  AV_PICTURE_TYPE_B 134 
#define  AV_PICTURE_TYPE_BI 133 
#define  AV_PICTURE_TYPE_I 132 
#define  AV_PICTURE_TYPE_P 131 
#define  AV_PICTURE_TYPE_S 130 
#define  AV_PICTURE_TYPE_SI 129 
#define  AV_PICTURE_TYPE_SP 128 
 int HB_FRAME_B ; 
 int HB_FRAME_I ; 
 int HB_FRAME_P ; 

__attribute__((used)) static int get_frame_type(int type)
{
    switch (type)
    {
        case AV_PICTURE_TYPE_B:
            return HB_FRAME_B;

        case AV_PICTURE_TYPE_S:
        case AV_PICTURE_TYPE_P:
        case AV_PICTURE_TYPE_SP:
            return HB_FRAME_P;

        case AV_PICTURE_TYPE_BI:
        case AV_PICTURE_TYPE_SI:
        case AV_PICTURE_TYPE_I:
        default:
            return HB_FRAME_I;
    }
}