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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int LPC_FILTERORDER ; 
 int /*<<< orphan*/  lsf2poly (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsf_interpolate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void lsp_interpolate2polydec(int16_t *a, int16_t *lsf1,
                                   int16_t *lsf2, int coef, int length)
{
    int16_t lsftmp[LPC_FILTERORDER];

    lsf_interpolate(lsftmp, lsf1, lsf2, coef, length);
    lsf2poly(a, lsftmp);
}