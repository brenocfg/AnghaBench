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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB24 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hflip_b24_c(const uint8_t *src, uint8_t *dst, int w)
{
    const uint8_t *in  = src;
    uint8_t *out = dst;
    int j;

    for (j = 0; j < w; j++, out += 3, in -= 3) {
        int32_t v = AV_RB24(in);

        AV_WB24(out, v);
    }
}