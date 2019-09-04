#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  err; int /*<<< orphan*/  notify; struct TYPE_7__* next; struct TYPE_7__* free_waiter; int /*<<< orphan*/  wait_next; int /*<<< orphan*/  wait_tail; int /*<<< orphan*/  wait_head; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * scanner; int /*<<< orphan*/ * syms; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  TYPE_1__ proc_waiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_event_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_processor_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_image_scanner_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_processor_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_symbol_set_ref (int /*<<< orphan*/ *,int) ; 

void zbar_processor_destroy (zbar_processor_t *proc)
{
    zbar_processor_init(proc, NULL, 0);

    if(proc->syms) {
        zbar_symbol_set_ref(proc->syms, -1);
        proc->syms = NULL;
    }
    if(proc->scanner) {
        zbar_image_scanner_destroy(proc->scanner);
        proc->scanner = NULL;
    }

    _zbar_mutex_destroy(&proc->mutex);
    _zbar_processor_cleanup(proc);

    assert(!proc->wait_head);
    assert(!proc->wait_tail);
    assert(!proc->wait_next);

    proc_waiter_t *w, *next;
    for(w = proc->free_waiter; w; w = next) {
        next = w->next;
        _zbar_event_destroy(&w->notify);
        free(w);
    }

    err_cleanup(&proc->err);
    free(proc);
}