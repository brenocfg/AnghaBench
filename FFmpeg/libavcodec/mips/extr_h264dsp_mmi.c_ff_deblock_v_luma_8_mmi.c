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
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_deblock_v8_luma_8_mmi (int /*<<< orphan*/ *,int,int,int,int*) ; 

void ff_deblock_v_luma_8_mmi(uint8_t *pix, int stride, int alpha, int beta,
        int8_t *tc0)
{
    if ((tc0[0] & tc0[1]) >= 0)
        ff_deblock_v8_luma_8_mmi(pix + 0, stride, alpha, beta, tc0);
    if ((tc0[2] & tc0[3]) >= 0)
        ff_deblock_v8_luma_8_mmi(pix + 8, stride, alpha, beta, tc0 + 2);
}