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
 double log10 (double) ; 

__attribute__((used)) static double avpriv_trc_log(double Lc)
{
    return (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}