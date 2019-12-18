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
struct ColorSystem {double gamma; } ;

/* Variables and functions */
 double pow (double,int) ; 

__attribute__((used)) static void
gamma_correct(const struct ColorSystem * const cs,
              double *                   const c)
{
/*----------------------------------------------------------------------------
    Transform linear RGB values to nonlinear RGB values.

    Rec. 709 is ITU-R Recommendation BT. 709 (1990)
    ``Basic Parameter Values for the HDTV Standard for the Studio and for
    International Programme Exchange'', formerly CCIR Rec. 709.

    For details see
       http://www.inforamp.net/~poynton/ColorFAQ.html
       http://www.inforamp.net/~poynton/GammaFAQ.html
-----------------------------------------------------------------------------*/
    double gamma;
    double cc;

    gamma = cs->gamma;

    if (gamma == 0.) {
        /* Rec. 709 gamma correction. */
        cc = 0.018;
        if (*c < cc) {
            *c *= (1.099 * pow(cc, 0.45) - 0.099) / cc;
        } else {
            *c = 1.099 * pow(*c, 0.45) - 0.099;
        }
    } else {
    /* Nonlinear color = (Linear color)^(1/gamma) */
        *c = pow(*c, 1./gamma);
    }
}