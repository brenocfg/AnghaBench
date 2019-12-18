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
 double pow (double,double) ; 

__attribute__((used)) static double avpriv_trc_smpte_st428_1(double Lc)
{
    return (0.0 > Lc) ? 0.0
         :              pow(48.0 * Lc / 52.37, 1.0 / 2.6);
}