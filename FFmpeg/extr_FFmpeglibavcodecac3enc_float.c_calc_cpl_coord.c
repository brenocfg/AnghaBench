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
typedef  int /*<<< orphan*/  CoefType ;
typedef  int CoefSumType ;

/* Variables and functions */
 int /*<<< orphan*/  COEF_MAX ; 
 int /*<<< orphan*/  FFMIN (float,int /*<<< orphan*/ ) ; 
 float sqrtf (int) ; 

__attribute__((used)) static CoefType calc_cpl_coord(CoefSumType energy_ch, CoefSumType energy_cpl)
{
    float coord = 0.125;
    if (energy_cpl > 0)
        coord *= sqrtf(energy_ch / energy_cpl);
    return FFMIN(coord, COEF_MAX);
}