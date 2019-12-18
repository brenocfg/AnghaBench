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
struct LumaCoefficients {int /*<<< orphan*/  cr; } ;
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;

/* Variables and functions */
 int AVCOL_SPC_NB ; 
 struct LumaCoefficients* luma_coefficients ; 

const struct LumaCoefficients *ff_get_luma_coefficients(enum AVColorSpace csp)
{
    const struct LumaCoefficients *coeffs;

    if (csp >= AVCOL_SPC_NB)
        return NULL;
    coeffs = &luma_coefficients[csp];
    if (!coeffs->cr)
        return NULL;

    return coeffs;
}