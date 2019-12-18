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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/  const*) ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extract_color (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dxt1_block_internal(uint8_t *dst, ptrdiff_t stride,
                                       const uint8_t *block, uint8_t alpha)
{
    int x, y;
    uint32_t colors[4];
    uint16_t color0 = AV_RL16(block + 0);
    uint16_t color1 = AV_RL16(block + 2);
    uint32_t code   = AV_RL32(block + 4);

    extract_color(colors, color0, color1, 0, alpha);

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            uint32_t pixel = colors[code & 3];
            code >>= 2;
            AV_WL32(dst + x * 4, pixel);
        }
        dst += stride;
    }
}