#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int metric_length; } ;
struct TYPE_11__ {int flags; scalar_t__ buffer; int affinity; int* vars; int* combs; TYPE_3__* next; TYPE_2__* prev; } ;
struct TYPE_10__ {int flags; int* vars; int* combs; TYPE_1__* next; scalar_t__ affinity; } ;
struct TYPE_9__ {int* vars; } ;
struct TYPE_8__ {scalar_t__ buffer; int affinity; int flags; } ;
typedef  TYPE_4__ PullupField ;
typedef  TYPE_5__ PullupContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int F_HAVE_AFFINITY ; 

__attribute__((used)) static void compute_affinity(PullupContext *s, PullupField *f)
{
    int i, max_l = 0, max_r = 0, l;

    if (f->flags & F_HAVE_AFFINITY)
        return;

    f->flags |= F_HAVE_AFFINITY;

    if (f->buffer == f->next->next->buffer) {
        f->affinity             =  1;
        f->next->affinity       =  0;
        f->next->next->affinity = -1;
        f->next->flags         |= F_HAVE_AFFINITY;
        f->next->next->flags   |= F_HAVE_AFFINITY;
        return;
    }

    for (i = 0; i < s->metric_length; i++) {
        int v  = f->vars[i];
        int lv = f->prev->vars[i];
        int rv = f->next->vars[i];
        int lc = f->      combs[i] - 2*(v < lv ? v : lv);
        int rc = f->next->combs[i] - 2*(v < rv ? v : rv);

        lc = FFMAX(lc, 0);
        rc = FFMAX(rc, 0);
        l  = lc - rc;

        if ( l > max_l)
            max_l =  l;
        if (-l > max_r)
            max_r = -l;
    }

    if (max_l + max_r < 64)
        return;

    if (max_r > 6 * max_l)
        f->affinity = -1;
    else if (max_l > 6 * max_r)
        f->affinity =  1;
}