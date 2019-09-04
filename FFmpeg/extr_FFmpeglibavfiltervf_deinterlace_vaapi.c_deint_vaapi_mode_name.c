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
#define  VAProcDeinterlacingBob 131 
#define  VAProcDeinterlacingMotionAdaptive 130 
#define  VAProcDeinterlacingMotionCompensated 129 
#define  VAProcDeinterlacingWeave 128 

__attribute__((used)) static const char *deint_vaapi_mode_name(int mode)
{
    switch (mode) {
#define D(name) case VAProcDeinterlacing ## name: return #name
        D(Bob);
        D(Weave);
        D(MotionAdaptive);
        D(MotionCompensated);
#undef D
    default:
        return "Invalid";
    }
}