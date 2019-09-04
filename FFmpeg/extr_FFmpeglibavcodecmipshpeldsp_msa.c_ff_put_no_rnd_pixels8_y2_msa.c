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

/* Variables and functions */
 int /*<<< orphan*/  common_vt_bil_no_rnd_4x8_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_vt_bil_no_rnd_8x8_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_put_no_rnd_pixels8_y2_msa(uint8_t *block, const uint8_t *pixels,
                                  ptrdiff_t line_size, int h)
{
    if (h == 8) {
        common_vt_bil_no_rnd_8x8_msa(pixels, line_size, block, line_size);
    } else if (h == 4) {
        common_vt_bil_no_rnd_4x8_msa(pixels, line_size, block, line_size);
    }
}