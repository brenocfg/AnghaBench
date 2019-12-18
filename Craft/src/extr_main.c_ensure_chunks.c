#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ Worker ;
struct TYPE_5__ {TYPE_1__* workers; } ;
typedef  int /*<<< orphan*/  Player ;

/* Variables and functions */
 int WORKERS ; 
 scalar_t__ WORKER_IDLE ; 
 int /*<<< orphan*/  check_workers () ; 
 int /*<<< orphan*/  ensure_chunks_worker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  force_chunks (int /*<<< orphan*/ *) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void ensure_chunks(Player *player) {
    check_workers();
    force_chunks(player);
    for (int i = 0; i < WORKERS; i++) {
        Worker *worker = g->workers + i;
        mtx_lock(&worker->mtx);
        if (worker->state == WORKER_IDLE) {
            ensure_chunks_worker(player, worker);
        }
        mtx_unlock(&worker->mtx);
    }
}