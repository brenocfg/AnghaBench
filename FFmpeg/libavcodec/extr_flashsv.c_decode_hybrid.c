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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (int const*) ; 
 int /*<<< orphan*/  bytestream_put_le24 (int**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_hybrid(const uint8_t *sptr, const uint8_t *sptr_end, uint8_t *dptr, int dx, int dy,
                         int h, int w, int stride, const uint32_t *pal)
{
    int x, y;
    const uint8_t *orig_src = sptr;

    for (y = dx + h; y > dx; y--) {
        uint8_t *dst = dptr + (y * stride) + dy * 3;
        for (x = 0; x < w; x++) {
            if (sptr >= sptr_end)
                return AVERROR_INVALIDDATA;
            if (*sptr & 0x80) {
                /* 15-bit color */
                unsigned c = AV_RB16(sptr) & ~0x8000;
                unsigned b =  c        & 0x1F;
                unsigned g = (c >>  5) & 0x1F;
                unsigned r =  c >> 10;
                /* 000aaabb -> aaabbaaa  */
                *dst++ = (b << 3) | (b >> 2);
                *dst++ = (g << 3) | (g >> 2);
                *dst++ = (r << 3) | (r >> 2);
                sptr += 2;
            } else {
                /* palette index */
                uint32_t c = pal[*sptr++];
                bytestream_put_le24(&dst, c);
            }
        }
    }
    return sptr - orig_src;
}