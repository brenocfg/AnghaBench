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
 int SWS_CS_DEFAULT ; 
 int const** ff_yuv2rgb_coeffs ; 

const int *sws_getCoefficients(int colorspace)
{
    if (colorspace > 10 || colorspace < 0 || colorspace == 8)
        colorspace = SWS_CS_DEFAULT;
    return ff_yuv2rgb_coeffs[colorspace];
}