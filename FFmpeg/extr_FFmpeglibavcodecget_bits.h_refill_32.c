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
struct TYPE_3__ {int index; int buffer_end; int buffer; int cache; int bits_left; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_RB32 (int) ; 
 scalar_t__ AV_RL32 (int) ; 

__attribute__((used)) static inline void refill_32(GetBitContext *s, int is_le)
{
#if !UNCHECKED_BITSTREAM_READER
    if (s->index >> 3 >= s->buffer_end - s->buffer)
        return;
#endif

    if (is_le)
    s->cache       = (uint64_t)AV_RL32(s->buffer + (s->index >> 3)) << s->bits_left | s->cache;
    else
    s->cache       = s->cache | (uint64_t)AV_RB32(s->buffer + (s->index >> 3)) << (32 - s->bits_left);
    s->index     += 32;
    s->bits_left += 32;
}