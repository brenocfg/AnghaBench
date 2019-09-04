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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 void* AV_RL16 (int const*) ; 
 int AV_RL32 (int const*) ; 
 int /*<<< orphan*/  AV_WL32 (int*,int) ; 
 int /*<<< orphan*/  extract_color (int*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dxt3_block_internal(uint8_t *dst, ptrdiff_t stride,
                                       const uint8_t *block)
{
    int x, y;
    uint32_t colors[4];
    uint16_t color0 = AV_RL16(block +  8);
    uint16_t color1 = AV_RL16(block + 10);
    uint32_t code   = AV_RL32(block + 12);

    extract_color(colors, color0, color1, 1, 0);

    for (y = 0; y < 4; y++) {
        const uint16_t alpha_code = AV_RL16(block + 2 * y);
        uint8_t alpha_values[4];

        alpha_values[0] = ((alpha_code >>  0) & 0x0F) * 17;
        alpha_values[1] = ((alpha_code >>  4) & 0x0F) * 17;
        alpha_values[2] = ((alpha_code >>  8) & 0x0F) * 17;
        alpha_values[3] = ((alpha_code >> 12) & 0x0F) * 17;

        for (x = 0; x < 4; x++) {
            uint8_t alpha = alpha_values[x];
            uint32_t pixel = colors[code & 3] | ((unsigned)alpha << 24);
            code >>= 2;

            AV_WL32(dst + x * 4, pixel);
        }
        dst += stride;
    }
}