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
struct TYPE_3__ {size_t rb_roundtrips; size_t partial_pos_out; scalar_t__ ringbuffer_size; scalar_t__ pos; } ;
typedef  TYPE_1__ BrotliDecoderState ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */

__attribute__((used)) static size_t UnwrittenBytes(const BrotliDecoderState* s, BROTLI_BOOL wrap) {
  size_t pos = wrap && s->pos > s->ringbuffer_size ?
      (size_t)s->ringbuffer_size : (size_t)(s->pos);
  size_t partial_pos_rb = (s->rb_roundtrips * (size_t)s->ringbuffer_size) + pos;
  return partial_pos_rb - s->partial_pos_out;
}