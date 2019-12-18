#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ PullupField ;
typedef  int /*<<< orphan*/  PullupContext ;

/* Variables and functions */
 scalar_t__ alloc_metrics (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  free_field_queue (TYPE_1__*) ; 

__attribute__((used)) static PullupField *make_field_queue(PullupContext *s, int len)
{
    PullupField *head, *f;

    f = head = av_mallocz(sizeof(*head));
    if (!f)
        return NULL;

    if (alloc_metrics(s, f) < 0) {
        av_free(f);
        return NULL;
    }

    for (; len > 0; len--) {
        f->next = av_mallocz(sizeof(*f->next));
        if (!f->next) {
            free_field_queue(head);
            return NULL;
        }

        f->next->prev = f;
        f = f->next;
        if (alloc_metrics(s, f) < 0) {
            free_field_queue(head);
            return NULL;
        }
    }

    f->next = head;
    head->prev = f;

    return head;
}