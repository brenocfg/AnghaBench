#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int size_in_bits; int size_in_bits_plus8; scalar_t__ bits_left; scalar_t__ cache; scalar_t__ index; int /*<<< orphan*/  const* buffer_end; int /*<<< orphan*/  const* buffer; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int FFMAX (int,int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  refill_64 (TYPE_1__*,int) ; 

__attribute__((used)) static inline int init_get_bits_xe(GetBitContext *s, const uint8_t *buffer,
                                   int bit_size, int is_le)
{
    int buffer_size;
    int ret = 0;

    if (bit_size >= INT_MAX - FFMAX(7, AV_INPUT_BUFFER_PADDING_SIZE*8) || bit_size < 0 || !buffer) {
        bit_size    = 0;
        buffer      = NULL;
        ret         = AVERROR_INVALIDDATA;
    }

    buffer_size = (bit_size + 7) >> 3;

    s->buffer             = buffer;
    s->size_in_bits       = bit_size;
    s->size_in_bits_plus8 = bit_size + 8;
    s->buffer_end         = buffer + buffer_size;
    s->index              = 0;

#if CACHED_BITSTREAM_READER
    s->cache              = 0;
    s->bits_left          = 0;
    refill_64(s, is_le);
#endif

    return ret;
}