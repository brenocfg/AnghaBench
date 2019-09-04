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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN32A (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_4x4_block(uint8_t *dst, int linesize, uint32_t pixel)
{
    int i, j;
    for (j = 0; j < 4; j++)
        for (i = 0; i < 4; i++)
            AV_WN32A(dst + j * linesize + i * 4, pixel);
}