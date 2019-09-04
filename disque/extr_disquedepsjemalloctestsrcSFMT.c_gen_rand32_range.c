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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sfmt_t ;

/* Variables and functions */
 int gen_rand32 (int /*<<< orphan*/ *) ; 

uint32_t gen_rand32_range(sfmt_t *ctx, uint32_t limit) {
    uint32_t ret, above;

    above = 0xffffffffU - (0xffffffffU % limit);
    while (1) {
	ret = gen_rand32(ctx);
	if (ret < above) {
	    ret %= limit;
	    break;
	}
    }
    return ret;
}