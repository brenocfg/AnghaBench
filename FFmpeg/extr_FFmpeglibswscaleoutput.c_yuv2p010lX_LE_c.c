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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  yuv2p010lX_c (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yuv2p010lX_LE_c(const int16_t *filter, int filterSize,
                            const int16_t **src, uint8_t *dest, int dstW,
                            const uint8_t *dither, int offset)
{
    yuv2p010lX_c(filter, filterSize, src, (uint16_t*)dest, dstW, 0);
}