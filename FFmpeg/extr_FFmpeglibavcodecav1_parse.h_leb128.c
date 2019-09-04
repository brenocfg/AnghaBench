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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int64_t leb128(GetBitContext *gb) {
    int64_t ret = 0;
    int i;

    for (i = 0; i < 8; i++) {
        int byte = get_bits(gb, 8);
        ret |= (int64_t)(byte & 0x7f) << (i * 7);
        if (!(byte & 0x80))
            break;
    }
    return ret;
}