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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int high; int bits; int /*<<< orphan*/  const* buffer; int /*<<< orphan*/  code_word; scalar_t__ end_reached; int /*<<< orphan*/  const* end; } ;
typedef  TYPE_1__ VP56RangeCoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  bytestream_get_be24 (int /*<<< orphan*/  const**) ; 

int ff_vp56_init_range_decoder(VP56RangeCoder *c, const uint8_t *buf, int buf_size)
{
    c->high = 255;
    c->bits = -16;
    c->buffer = buf;
    c->end = buf + buf_size;
    c->end_reached = 0;
    if (buf_size < 1)
        return AVERROR_INVALIDDATA;
    c->code_word = bytestream_get_be24(&c->buffer);
    return 0;
}