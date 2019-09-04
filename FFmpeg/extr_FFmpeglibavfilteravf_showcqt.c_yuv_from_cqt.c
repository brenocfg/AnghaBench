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
struct TYPE_6__ {float y; float u; float v; } ;
struct TYPE_8__ {TYPE_1__ yuv; } ;
struct TYPE_7__ {float re; float im; } ;
typedef  TYPE_2__ FFTComplex ;
typedef  TYPE_3__ ColorFloat ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (float,float) ; 
 float calculate_gamma (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void yuv_from_cqt(ColorFloat *c, const FFTComplex *v, float gamma, int len, float cm[3][3], float cscheme[6])
{
    int x;
    for (x = 0; x < len; x++) {
        float r, g, b;
        r = calculate_gamma(FFMIN(1.0f, cscheme[0] * v[x].re + cscheme[3] * v[x].im), gamma);
        g = calculate_gamma(FFMIN(1.0f, cscheme[1] * v[x].re + cscheme[4] * v[x].im), gamma);
        b = calculate_gamma(FFMIN(1.0f, cscheme[2] * v[x].re + cscheme[5] * v[x].im), gamma);
        c[x].yuv.y = cm[0][0] * r + cm[0][1] * g + cm[0][2] * b;
        c[x].yuv.u = cm[1][0] * r + cm[1][1] * g + cm[1][2] * b;
        c[x].yuv.v = cm[2][0] * r + cm[2][1] * g + cm[2][2] * b;
    }
}