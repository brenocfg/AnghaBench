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
struct TYPE_3__ {float* s; } ;
typedef  TYPE_1__ cl_float2 ;

/* Variables and functions */
 int /*<<< orphan*/  ff_get_matrix (float,float,float,float,float,float*) ; 
 TYPE_1__ transformed_point (float,float,float*) ; 

__attribute__((used)) static void transform_center_scale(
    float x_shift,
    float y_shift,
    float angle,
    float scale_x,
    float scale_y,
    float center_w,
    float center_h,
    float *matrix
) {
    cl_float2 center_s;
    float center_s_w, center_s_h;

    ff_get_matrix(
        0,
        0,
        0,
        scale_x,
        scale_y,
        matrix
    );

    center_s = transformed_point(center_w, center_h, matrix);
    center_s_w = center_w - center_s.s[0];
    center_s_h = center_h - center_s.s[1];

    ff_get_matrix(
        x_shift + center_s_w,
        y_shift + center_s_h,
        angle,
        scale_x,
        scale_y,
        matrix
    );
}