#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pullup_context {int nbuffers; TYPE_2__* buffers; TYPE_1__* last; } ;
struct pullup_buffer {int dummy; } ;
struct TYPE_5__ {scalar_t__* lock; } ;
struct TYPE_4__ {int parity; TYPE_2__* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  pullup_alloc_buffer (struct pullup_context*,TYPE_2__*) ; 
 struct pullup_buffer* pullup_lock_buffer (TYPE_2__*,int) ; 

struct pullup_buffer * pullup_get_buffer( struct pullup_context * c,
                                          int parity )
{
    int i;

    /* Try first to get the sister buffer for the previous field */
    if( parity < 2 &&
        c->last &&
        parity != c->last->parity &&
        !c->last->buffer->lock[parity])
    {
        pullup_alloc_buffer( c, c->last->buffer );
        return pullup_lock_buffer( c->last->buffer, parity );
    }

    /* Prefer a buffer with both fields open */
    for( i = 0; i < c->nbuffers; i++ )
    {
        if( c->buffers[i].lock[0] ) continue;
        if( c->buffers[i].lock[1] ) continue;
        pullup_alloc_buffer( c, &c->buffers[i] );
        return pullup_lock_buffer( &c->buffers[i], parity );
    }

    if( parity == 2 ) return 0;

    /* Search for any half-free buffer */
    for( i = 0; i < c->nbuffers; i++ )
    {
        if( ((parity+1) & 1) && c->buffers[i].lock[0] ) continue;
        if( ((parity+1) & 2) && c->buffers[i].lock[1] ) continue;
        pullup_alloc_buffer( c, &c->buffers[i] );
        return pullup_lock_buffer( &c->buffers[i], parity );
    }

    return 0;
}