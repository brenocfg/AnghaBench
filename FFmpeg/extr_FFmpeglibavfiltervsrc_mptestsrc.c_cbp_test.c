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
 int /*<<< orphan*/  draw_cbp (int /*<<< orphan*/ **,int*,int,int,int) ; 

__attribute__((used)) static void cbp_test(uint8_t *dst[3], int dst_linesize[3], int off)
{
    int x, y, cbp = 0;

    for (y = 0; y < 16*8; y += 16) {
        for (x = 0; x < 16*8; x += 16) {
            uint8_t *dst1[3];
            dst1[0] = dst[0] + x*2 + y*2*dst_linesize[0];
            dst1[1] = dst[1] + x   + y*  dst_linesize[1];
            dst1[2] = dst[2] + x   + y*  dst_linesize[2];

            draw_cbp(dst1, dst_linesize, cbp, (64+off)*4, 128*8);
            cbp++;
        }
    }
}