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
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int MIN_CACHE_BITS ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bit_copy(PutBitContext *pb, GetBitContext *gb)
{
    int bits_left = get_bits_left(gb);
    while (bits_left >= MIN_CACHE_BITS) {
        put_bits(pb, MIN_CACHE_BITS, get_bits(gb, MIN_CACHE_BITS));
        bits_left -= MIN_CACHE_BITS;
    }
    if (bits_left > 0)
        put_bits(pb, bits_left, get_bits(gb, bits_left));
}