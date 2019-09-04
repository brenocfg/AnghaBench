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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOWPASS (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void intra_pred_lp_top(uint8_t *d, uint8_t *top, uint8_t *left, ptrdiff_t stride)
{
    int x, y;
    for (y = 0; y < 8; y++)
        for (x = 0; x < 8; x++)
            d[y * stride + x] = LOWPASS(top, x + 1);
}