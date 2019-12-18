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
struct pullup_field {struct pullup_field* next; } ;
struct pullup_context {int /*<<< orphan*/  last; struct pullup_field* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  pullup_compute_affinity (struct pullup_context*,struct pullup_field*) ; 
 int /*<<< orphan*/  pullup_compute_breaks (struct pullup_context*,struct pullup_field*) ; 
 int pullup_queue_length (struct pullup_field*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pullup_foo( struct pullup_context * c )
{
    struct pullup_field * f = c->first;
    int i, n = pullup_queue_length (f, c->last );
    for( i = 0; i < n-1; i++ )
    {
        if( i < n-3 ) pullup_compute_breaks( c, f );
        pullup_compute_affinity( c, f );
        f = f->next;
    }
}