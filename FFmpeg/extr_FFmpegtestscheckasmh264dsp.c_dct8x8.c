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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  dct8x8_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dct8x8_32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dct8x8(int16_t *coef, int bit_depth)
{
    if (bit_depth == 8) {
        dct8x8_16(coef);
    } else {
        dct8x8_32((int32_t *) coef);
    }
}