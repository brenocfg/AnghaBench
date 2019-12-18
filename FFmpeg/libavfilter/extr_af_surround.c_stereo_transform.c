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
 int FFDIFFSIGN (float,int /*<<< orphan*/ ) ; 
 float M_PI ; 
 float M_PI_2 ; 
 float M_PI_4 ; 
 float atan2f (float,float) ; 
 float av_clipf (float,int,int) ; 
 float cosf (float) ; 
 float fabsf (float) ; 
 float hypotf (float,float) ; 
 float sinf (float) ; 

__attribute__((used)) static void stereo_transform(float *x, float *y, float angle)
{
    float reference, r, a;

    if (angle == 90.f)
        return;

    reference = angle * M_PI / 180.f;
    r = hypotf(*x, *y);
    a = atan2f(*x, *y);

    if (fabsf(a) <= M_PI_4)
        a *= reference / M_PI_2;
    else
        a = M_PI + 2 * (-2 * M_PI + reference) * (M_PI - fabsf(a)) * FFDIFFSIGN(a, 0) / (3 * M_PI);

    *x = av_clipf(sinf(a) * r, -1, 1);
    *y = av_clipf(cosf(a) * r, -1, 1);
}