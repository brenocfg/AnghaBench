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
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 double av_lfg_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double dbl_rand(AVLFG *lfg)
{
    return 2.0 * (av_lfg_get(lfg) / (double)UINT_MAX) - 1.0;
}