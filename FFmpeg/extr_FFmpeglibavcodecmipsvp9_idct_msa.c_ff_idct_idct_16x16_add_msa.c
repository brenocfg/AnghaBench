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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  vp9_idct16x16_10_colcol_addblk_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp9_idct16x16_1_add_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp9_idct16x16_colcol_addblk_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_idct_idct_16x16_add_msa(uint8_t *dst, ptrdiff_t stride,
                                int16_t *block, int eob)
{
    if (eob == 1) {
        /* DC only DCT coefficient. */
        vp9_idct16x16_1_add_msa(block, dst, stride);
    }
    else if (eob <= 10) {
        vp9_idct16x16_10_colcol_addblk_msa(block, dst, stride);
    }
    else {
        vp9_idct16x16_colcol_addblk_msa(block, dst, stride);
    }
}