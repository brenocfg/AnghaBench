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
 int /*<<< orphan*/  ff_put_pixels_clamped_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_simple_idct_8_mmi (int /*<<< orphan*/ *) ; 

void ff_simple_idct_put_8_mmi(uint8_t *dest, ptrdiff_t line_size, int16_t *block)
{
    ff_simple_idct_8_mmi(block);
    ff_put_pixels_clamped_mmi(block, dest, line_size);
}