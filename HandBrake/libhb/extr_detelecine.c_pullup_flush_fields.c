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
struct pullup_field {scalar_t__ buffer; int /*<<< orphan*/  parity; struct pullup_field* next; } ;
struct pullup_context {struct pullup_field* last; struct pullup_field* first; struct pullup_field* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  pullup_release_buffer (scalar_t__,int /*<<< orphan*/ ) ; 

void pullup_flush_fields( struct pullup_context * c )
{
    struct pullup_field * f;

    for( f = c->first; f && f != c->head; f = f->next )
    {
        pullup_release_buffer( f->buffer, f->parity );
        f->buffer = 0;
    }
    c->first = c->last = 0;
}