#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__* lock; } ;
struct TYPE_9__ {TYPE_3__* buffers; TYPE_1__* last; } ;
struct TYPE_8__ {int parity; TYPE_3__* buffer; } ;
typedef  TYPE_2__ PullupContext ;
typedef  int /*<<< orphan*/  PullupBuffer ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int /*<<< orphan*/  alloc_buffer (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * pullup_lock_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static PullupBuffer *pullup_get_buffer(PullupContext *s, int parity)
{
    int i;

    /* Try first to get the sister buffer for the previous field */
    if (parity < 2 && s->last && parity != s->last->parity
        && !s->last->buffer->lock[parity]) {
        alloc_buffer(s, s->last->buffer);
        return pullup_lock_buffer(s->last->buffer, parity);
    }

    /* Prefer a buffer with both fields open */
    for (i = 0; i < FF_ARRAY_ELEMS(s->buffers); i++) {
        if (s->buffers[i].lock[0])
            continue;
        if (s->buffers[i].lock[1])
            continue;
        alloc_buffer(s, &s->buffers[i]);
        return pullup_lock_buffer(&s->buffers[i], parity);
    }

    if (parity == 2)
        return 0;

    /* Search for any half-free buffer */
    for (i = 0; i < FF_ARRAY_ELEMS(s->buffers); i++) {
        if (((parity + 1) & 1) && s->buffers[i].lock[0])
            continue;
        if (((parity + 1) & 2) && s->buffers[i].lock[1])
            continue;
        alloc_buffer(s, &s->buffers[i]);
        return pullup_lock_buffer(&s->buffers[i], parity);
    }

    return NULL;
}