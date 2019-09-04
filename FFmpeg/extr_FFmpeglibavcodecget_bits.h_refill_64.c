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
struct TYPE_3__ {int index; int buffer_end; int buffer; int bits_left; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB64 (int) ; 
 int /*<<< orphan*/  AV_RL64 (int) ; 

__attribute__((used)) static inline void refill_64(GetBitContext *s, int is_le)
{
#if !UNCHECKED_BITSTREAM_READER
    if (s->index >> 3 >= s->buffer_end - s->buffer)
        return;
#endif

    if (is_le)
    s->cache = AV_RL64(s->buffer + (s->index >> 3));
    else
    s->cache = AV_RB64(s->buffer + (s->index >> 3));
    s->index += 64;
    s->bits_left = 64;
}