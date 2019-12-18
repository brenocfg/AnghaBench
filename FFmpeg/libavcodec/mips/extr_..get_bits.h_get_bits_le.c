#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int bits_left; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SHOW_UBITS_LE (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  UPDATE_CACHE_LE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 unsigned int get_val (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  re ; 
 int /*<<< orphan*/  refill_32 (TYPE_1__*,int) ; 

__attribute__((used)) static inline unsigned int get_bits_le(GetBitContext *s, int n)
{
#if CACHED_BITSTREAM_READER
    av_assert2(n>0 && n<=32);
    if (n > s->bits_left) {
        refill_32(s, 1);
        if (s->bits_left < 32)
            s->bits_left = n;
    }

    return get_val(s, n, 1);
#else
    register int tmp;
    OPEN_READER(re, s);
    av_assert2(n>0 && n<=25);
    UPDATE_CACHE_LE(re, s);
    tmp = SHOW_UBITS_LE(re, s, n);
    LAST_SKIP_BITS(re, s, n);
    CLOSE_READER(re, s);
    return tmp;
#endif
}