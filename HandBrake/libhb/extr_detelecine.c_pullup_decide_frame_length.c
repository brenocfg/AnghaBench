#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pullup_field {int affinity; int breaks; TYPE_1__* prev; struct pullup_field* next; } ;
struct pullup_context {scalar_t__ strict_breaks; int /*<<< orphan*/  strict_pairs; int /*<<< orphan*/  last; struct pullup_field* first; } ;
struct TYPE_2__ {int breaks; } ;

/* Variables and functions */
 int PULLUP_BREAK_LEFT ; 
 int PULLUP_BREAK_RIGHT ; 
 int pullup_find_first_break (struct pullup_field*,int) ; 
 int /*<<< orphan*/  pullup_foo (struct pullup_context*) ; 
 int pullup_queue_length (struct pullup_field*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pullup_decide_frame_length( struct pullup_context * c )
{
    struct pullup_field *f0 = c->first;
    struct pullup_field *f1 = f0->next;
    struct pullup_field *f2 = f1->next;
    int l;

    if( pullup_queue_length( c->first, c->last ) < 4 )
    {
        return 0;
    }
    pullup_foo( c );

    if( f0->affinity == -1 ) return 1;

    l = pullup_find_first_break( f0, 3 );
    if( l == 1 && c->strict_breaks < 0 ) l = 0;

    switch (l)
    {
        case 1:
            if ( c->strict_breaks < 1 &&
                 f0->affinity == 1 &&
                 f1->affinity == -1 )
            {
                return 2;
            }
            else
            {
                return 1;
            }

        case 2:
            /* FIXME: strictly speaking, f0->prev is no longer valid... :) */
            if( c->strict_pairs &&
                (f0->prev->breaks & PULLUP_BREAK_RIGHT) &&
                (f2->breaks & PULLUP_BREAK_LEFT) &&
                (f0->affinity != 1 || f1->affinity != -1) )
            {
                return 1;
            }
            if( f1->affinity == 1 )
            {
                return 1;
            }
            else
            {
                return 2;
            }

        case 3:
            if( f2->affinity == 1 )
            {
                return 2;
            }
            else
            {
                return 3;
            }

        default:
            /* 9 possibilities covered before switch */
            if( f1->affinity == 1 )
            {
                return 1; /* covers 6 */
            }
            else if( f1->affinity == -1 )
            {
                return 2; /* covers 6 */
            }
            else if( f2->affinity == -1 )
            {
                /* covers 2 */
                if( f0->affinity == 1 )
                {
                    return 3;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 2; /* the remaining 6 */
            }
    }
}