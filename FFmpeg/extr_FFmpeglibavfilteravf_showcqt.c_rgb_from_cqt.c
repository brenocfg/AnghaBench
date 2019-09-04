#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float r; float g; float b; } ;
struct TYPE_8__ {TYPE_1__ rgb; } ;
struct TYPE_7__ {float re; float im; } ;
typedef  TYPE_2__ FFTComplex ;
typedef  TYPE_3__ ColorFloat ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (float,float) ; 
 float calculate_gamma (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void rgb_from_cqt(ColorFloat *c, const FFTComplex *v, float g, int len, float cscheme[6])
{
    int x;
    for (x = 0; x < len; x++) {
        c[x].rgb.r = 255.0f * calculate_gamma(FFMIN(1.0f, cscheme[0] * v[x].re + cscheme[3] * v[x].im), g);
        c[x].rgb.g = 255.0f * calculate_gamma(FFMIN(1.0f, cscheme[1] * v[x].re + cscheme[4] * v[x].im), g);
        c[x].rgb.b = 255.0f * calculate_gamma(FFMIN(1.0f, cscheme[2] * v[x].re + cscheme[5] * v[x].im), g);
    }
}