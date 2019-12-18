#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pullup_frame {int length; TYPE_1__** ofields; TYPE_1__* buffer; } ;
struct pullup_context {int dummy; } ;
struct TYPE_5__ {scalar_t__* lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pullup_copy_field (struct pullup_context*,TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* pullup_get_buffer (struct pullup_context*,int) ; 
 int /*<<< orphan*/  pullup_lock_buffer (TYPE_1__*,int) ; 

void pullup_pack_frame( struct pullup_context * c, struct pullup_frame * fr)
{
    int i;
    if (fr->buffer) return;
    if (fr->length < 2) return; /* FIXME: deal with this */
    for( i = 0; i < 2; i++ )
    {
        if( fr->ofields[i]->lock[i^1] ) continue;
        fr->buffer = fr->ofields[i];
        pullup_lock_buffer(fr->buffer, 2);
        pullup_copy_field( c, fr->buffer, fr->ofields[i^1], i^1 );
        return;
    }
    fr->buffer = pullup_get_buffer( c, 2 );
    pullup_copy_field( c, fr->buffer, fr->ofields[0], 0 );
    pullup_copy_field( c, fr->buffer, fr->ofields[1], 1 );
}