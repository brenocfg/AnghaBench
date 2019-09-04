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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB48 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_WB48 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hflip_b48_c(const uint8_t *src, uint8_t *dst, int w)
{
    const uint8_t *in  = src;
    uint8_t *out = dst;
    int j;

    for (j = 0; j < w; j++, out += 6, in -= 6) {
        int64_t v = AV_RB48(in);

        AV_WB48(out, v);
    }
}