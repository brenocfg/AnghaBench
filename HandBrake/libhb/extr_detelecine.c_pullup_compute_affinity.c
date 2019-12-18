#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pullup_field {int flags; scalar_t__ buffer; int affinity; int* var; int* comb; TYPE_3__* next; TYPE_2__* prev; } ;
struct pullup_context {int metric_len; } ;
struct TYPE_6__ {int flags; int* var; int* comb; TYPE_1__* next; scalar_t__ affinity; } ;
struct TYPE_5__ {int* var; } ;
struct TYPE_4__ {scalar_t__ buffer; int affinity; int flags; } ;

/* Variables and functions */
 int PULLUP_ABS (int) ; 
 int PULLUP_HAVE_AFFINITY ; 

__attribute__((used)) static void pullup_compute_affinity( struct pullup_context * c,
                                     struct pullup_field * f )
{
    int i;
    int max_l = 0, max_r = 0, l;

    if( f->flags & PULLUP_HAVE_AFFINITY )
    {
        return;
    }
    f->flags |= PULLUP_HAVE_AFFINITY;

    if( f->buffer == f->next->next->buffer )
    {
        f->affinity             =  1;
        f->next->affinity       =  0;
        f->next->next->affinity = -1;

        f->next->flags       |= PULLUP_HAVE_AFFINITY;
        f->next->next->flags |= PULLUP_HAVE_AFFINITY;

        return;
    }

    for( i = 0; i < c->metric_len; i++ )
    {
        int lv = f->prev->var[i];
        int rv = f->next->var[i];
        int v  = f->var[i];
        int lc = f->comb[i] - (v+lv) + PULLUP_ABS( v-lv );
        int rc = f->next->comb[i] - (v+rv) + PULLUP_ABS( v-rv );

        lc = (lc > 0) ? lc : 0;
        rc = (rc > 0) ? rc : 0;
        l = lc - rc;
        if(  l > max_l ) max_l = l;
        if( -l > max_r ) max_r = -l;
    }

    if( max_l + max_r < 64 )
    {
        return;
    }

    if( max_r > 6*max_l )
    {
        f->affinity = -1;
    }
    else if( max_l > 6*max_r )
    {
        f->affinity = 1;
    }
}