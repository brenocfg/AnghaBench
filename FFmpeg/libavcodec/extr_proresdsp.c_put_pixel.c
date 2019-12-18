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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_10 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CLIP_12 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void put_pixel(uint16_t *dst, ptrdiff_t linesize, const int16_t *in, int bits_per_raw_sample) {
    int x, y, src_offset, dst_offset;

    for (y = 0, dst_offset = 0; y < 8; y++, dst_offset += linesize) {
        for (x = 0; x < 8; x++) {
            src_offset = (y << 3) + x;

            if (bits_per_raw_sample == 10) {
                dst[dst_offset + x] = CLIP_10(in[src_offset]);
            } else {//12b
                dst[dst_offset + x] = CLIP_12(in[src_offset]);
            }
        }
    }
}