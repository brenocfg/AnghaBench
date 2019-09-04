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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void rgba64leToA_c(uint8_t *_dst, const uint8_t *_src, const uint8_t *unused1,
                          const uint8_t *unused2, int width, uint32_t *unused)
{
    int16_t *dst = (int16_t *)_dst;
    const uint16_t *src = (const uint16_t *)_src;
    int i;
    for (i = 0; i < width; i++)
        dst[i] = AV_RL16(src + 4 * i + 3);
}