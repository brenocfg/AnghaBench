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
struct TYPE_3__ {int size_in_bits; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * buf_ptr; int /*<<< orphan*/ * buf_end; } ;
typedef  TYPE_1__ PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static inline void rebase_put_bits(PutBitContext *s, uint8_t *buffer,
                                   int buffer_size)
{
    av_assert0(8*buffer_size > s->size_in_bits);

    s->buf_end = buffer + buffer_size;
    s->buf_ptr = buffer + (s->buf_ptr - s->buf);
    s->buf     = buffer;
    s->size_in_bits = 8 * buffer_size;
}