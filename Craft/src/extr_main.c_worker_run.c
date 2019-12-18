#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ load; } ;
typedef  TYPE_1__ WorkerItem ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  mtx; TYPE_1__ item; int /*<<< orphan*/  cnd; } ;
typedef  TYPE_2__ Worker ;

/* Variables and functions */
 scalar_t__ WORKER_BUSY ; 
 scalar_t__ WORKER_DONE ; 
 int /*<<< orphan*/  cnd_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  load_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int worker_run(void *arg) {
    Worker *worker = (Worker *)arg;
    int running = 1;
    while (running) {
        mtx_lock(&worker->mtx);
        while (worker->state != WORKER_BUSY) {
            cnd_wait(&worker->cnd, &worker->mtx);
        }
        mtx_unlock(&worker->mtx);
        WorkerItem *item = &worker->item;
        if (item->load) {
            load_chunk(item);
        }
        compute_chunk(item);
        mtx_lock(&worker->mtx);
        worker->state = WORKER_DONE;
        mtx_unlock(&worker->mtx);
    }
    return 0;
}