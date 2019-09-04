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

/* Variables and functions */
 int /*<<< orphan*/  draw_basis (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void freq_test(uint8_t *dst, int dst_linesize, int off)
{
    int x, y, freq = 0;

    for (y = 0; y < 8*16; y += 16) {
        for (x = 0; x < 8*16; x += 16) {
            draw_basis(dst + x + y*dst_linesize, dst_linesize, 4*(96+off), freq, 128*8);
            freq++;
        }
    }
}