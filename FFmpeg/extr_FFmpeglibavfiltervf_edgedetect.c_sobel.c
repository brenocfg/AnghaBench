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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ FFABS (int const) ; 
 int /*<<< orphan*/  get_rounded_direction (int const,int const) ; 

__attribute__((used)) static void sobel(int w, int h,
                       uint16_t *dst, int dst_linesize,
                         int8_t *dir, int dir_linesize,
                  const uint8_t *src, int src_linesize)
{
    int i, j;

    for (j = 1; j < h - 1; j++) {
        dst += dst_linesize;
        dir += dir_linesize;
        src += src_linesize;
        for (i = 1; i < w - 1; i++) {
            const int gx =
                -1*src[-src_linesize + i-1] + 1*src[-src_linesize + i+1]
                -2*src[                i-1] + 2*src[                i+1]
                -1*src[ src_linesize + i-1] + 1*src[ src_linesize + i+1];
            const int gy =
                -1*src[-src_linesize + i-1] + 1*src[ src_linesize + i-1]
                -2*src[-src_linesize + i  ] + 2*src[ src_linesize + i  ]
                -1*src[-src_linesize + i+1] + 1*src[ src_linesize + i+1];

            dst[i] = FFABS(gx) + FFABS(gy);
            dir[i] = get_rounded_direction(gx, gy);
        }
    }
}