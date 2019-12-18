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

/* Variables and functions */
 int /*<<< orphan*/  cnd ; 
 int /*<<< orphan*/  cnd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnd_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  load_mtx ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring ; 
 int /*<<< orphan*/  ring_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_put_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thrd ; 
 int /*<<< orphan*/  thrd_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void db_worker_stop() {
    if (!db_enabled) {
        return;
    }
    mtx_lock(&mtx);
    ring_put_exit(&ring);
    cnd_signal(&cnd);
    mtx_unlock(&mtx);
    thrd_join(thrd, NULL);
    cnd_destroy(&cnd);
    mtx_destroy(&load_mtx);
    mtx_destroy(&mtx);
    ring_free(&ring);
}