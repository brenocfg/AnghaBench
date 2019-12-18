#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {unsigned int cache; unsigned int bits_left; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 unsigned int UINT64_C (int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static inline uint64_t get_val(GetBitContext *s, unsigned n, int is_le)
{
    uint64_t ret;
    av_assert2(n>0 && n<=63);
    if (is_le) {
        ret = s->cache & ((UINT64_C(1) << n) - 1);
        s->cache >>= n;
    } else {
        ret = s->cache >> (64 - n);
        s->cache <<= n;
    }
    s->bits_left -= n;
    return ret;
}