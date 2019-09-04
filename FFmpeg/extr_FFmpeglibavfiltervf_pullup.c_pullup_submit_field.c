#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* head; TYPE_1__* last; TYPE_1__* first; int /*<<< orphan*/  var; int /*<<< orphan*/  comb; int /*<<< orphan*/  diff; } ;
struct TYPE_8__ {int parity; struct TYPE_8__* next; int /*<<< orphan*/  vars; struct TYPE_8__* prev; int /*<<< orphan*/  combs; int /*<<< orphan*/  diffs; scalar_t__ affinity; scalar_t__ breaks; scalar_t__ flags; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ PullupField ;
typedef  TYPE_2__ PullupContext ;
typedef  int /*<<< orphan*/  PullupBuffer ;

/* Variables and functions */
 scalar_t__ check_field_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  compute_metric (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  pullup_lock_buffer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pullup_submit_field(PullupContext *s, PullupBuffer *b, int parity)
{
    PullupField *f;

    /* Grow the circular list if needed */
    if (check_field_queue(s) < 0)
        return;

    /* Cannot have two fields of same parity in a row; drop the new one */
    if (s->last && s->last->parity == parity)
        return;

    f = s->head;
    f->parity   = parity;
    f->buffer   = pullup_lock_buffer(b, parity);
    f->flags    = 0;
    f->breaks   = 0;
    f->affinity = 0;

    compute_metric(s, f->diffs, f, parity, f->prev->prev, parity, s->diff);
    compute_metric(s, f->combs, parity ? f->prev : f, 0, parity ? f : f->prev, 1, s->comb);
    compute_metric(s, f->vars, f, parity, f, -1, s->var);
    emms_c();

    /* Advance the circular list */
    if (!s->first)
        s->first = s->head;

    s->last = s->head;
    s->head = s->head->next;
}