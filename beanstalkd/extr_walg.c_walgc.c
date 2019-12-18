#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nfile; TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_1__ Wal ;
struct TYPE_7__ {struct TYPE_7__* path; struct TYPE_7__* next; int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  unlink (TYPE_2__*) ; 

void
walgc(Wal *w)
{
    File *f;

    while (w->head && !w->head->refs) {
        f = w->head;
        w->head = f->next;
        if (w->tail == f) {
            w->tail = f->next; // also, f->next == NULL
        }

        w->nfile--;
        unlink(f->path);
        free(f->path);
        free(f);
    }
}