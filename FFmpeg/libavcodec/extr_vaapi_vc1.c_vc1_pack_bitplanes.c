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

/* Variables and functions */

__attribute__((used)) static inline void vc1_pack_bitplanes(uint8_t *bitplane, int n, const uint8_t *ff_bp[3], int x, int y, int stride)
{
    const int bitplane_index = n / 2;
    const int ff_bp_index = y * stride + x;
    uint8_t v = 0;
    if (ff_bp[0])
        v = ff_bp[0][ff_bp_index];
    if (ff_bp[1])
        v |= ff_bp[1][ff_bp_index] << 1;
    if (ff_bp[2])
        v |= ff_bp[2][ff_bp_index] << 2;
    bitplane[bitplane_index] = (bitplane[bitplane_index] << 4) | v;
}