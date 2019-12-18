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
 int /*<<< orphan*/  cnd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  db_worker_run ; 
 int /*<<< orphan*/  load_mtx ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_plain ; 
 int /*<<< orphan*/  ring ; 
 int /*<<< orphan*/  ring_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thrd ; 
 int /*<<< orphan*/  thrd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void db_worker_start(char *path) {
    if (!db_enabled) {
        return;
    }
    ring_alloc(&ring, 1024);
    mtx_init(&mtx, mtx_plain);
    mtx_init(&load_mtx, mtx_plain);
    cnd_init(&cnd);
    thrd_create(&thrd, db_worker_run, path);
}