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
typedef  int uint16_t ;

/* Variables and functions */
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void blend_line16(uint8_t *dst, unsigned src, unsigned alpha,
                         int dx, int w, unsigned hsub, int left, int right)
{
    unsigned asrc = alpha * src;
    unsigned tau = 0x10001 - alpha;
    int x;

    if (left) {
        unsigned suba = (left * alpha) >> hsub;
        uint16_t value = AV_RL16(dst);
        AV_WL16(dst, (value * (0x10001 - suba) + src * suba) >> 16);
        dst += dx;
    }
    for (x = 0; x < w; x++) {
        uint16_t value = AV_RL16(dst);
        AV_WL16(dst, (value * tau + asrc) >> 16);
        dst += dx;
    }
    if (right) {
        unsigned suba = (right * alpha) >> hsub;
        uint16_t value = AV_RL16(dst);
        AV_WL16(dst, (value * (0x10001 - suba) + src * suba) >> 16);
    }
}