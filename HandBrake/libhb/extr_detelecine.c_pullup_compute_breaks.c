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
struct pullup_field {int flags; scalar_t__ buffer; int* diffs; int /*<<< orphan*/  breaks; struct pullup_field* next; } ;
struct pullup_context {int metric_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PULLUP_BREAK_LEFT ; 
 int /*<<< orphan*/  PULLUP_BREAK_RIGHT ; 
 int PULLUP_HAVE_BREAKS ; 

__attribute__((used)) static void pullup_compute_breaks( struct pullup_context * c,
                                   struct pullup_field * f0 )
{
    int i;
    struct pullup_field *f1 = f0->next;
    struct pullup_field *f2 = f1->next;
    struct pullup_field *f3 = f2->next;
    int l, max_l=0, max_r=0;

    if( f0->flags & PULLUP_HAVE_BREAKS ) return;
    f0->flags |= PULLUP_HAVE_BREAKS;

    /* Special case when fields are 100% identical */
    if( f0->buffer == f2->buffer && f1->buffer != f3->buffer )
    {
        f2->breaks |= PULLUP_BREAK_RIGHT;
        return;
    }
    if( f0->buffer != f2->buffer && f1->buffer == f3->buffer )
    {
        f1->breaks |= PULLUP_BREAK_LEFT;
        return;
    }

    for( i = 0; i < c->metric_len; i++ )
    {
        l = f2->diffs[i] - f3->diffs[i];
        if(  l > max_l) max_l = l;
        if( -l > max_r) max_r = -l;
    }

    /* Don't get tripped up when differences are mostly quant error */
    if( max_l + max_r < 128 ) return;
    if( max_l > 4*max_r ) f1->breaks |= PULLUP_BREAK_LEFT;
    if( max_r > 4*max_l ) f2->breaks |= PULLUP_BREAK_RIGHT;
}