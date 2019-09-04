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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_add_pixels_clamped_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_xvid_idct_mmi (int /*<<< orphan*/ *) ; 

void ff_xvid_idct_add_mmi(uint8_t *dest, int32_t line_size, int16_t *block)
{
    ff_xvid_idct_mmi(block);
    ff_add_pixels_clamped_mmi(block, dest, line_size);
}