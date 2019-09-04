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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  output_pixel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void yuv2p010l1_c(const int16_t *src,
                         uint16_t *dest, int dstW,
                         int big_endian)
{
    int i;
    int shift = 5;

    for (i = 0; i < dstW; i++) {
        int val = src[i] + (1 << (shift - 1));
        output_pixel(&dest[i], val);
    }
}