#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  key; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ RingEntry ;

/* Variables and functions */
#define  BLOCK 132 
#define  COMMIT 131 
#define  EXIT 130 
#define  KEY 129 
#define  LIGHT 128 
 int /*<<< orphan*/  _db_commit () ; 
 int /*<<< orphan*/  _db_insert_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _db_insert_light (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _db_set_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnd ; 
 int /*<<< orphan*/  cnd_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring ; 
 int /*<<< orphan*/  ring_get (int /*<<< orphan*/ *,TYPE_1__*) ; 

int db_worker_run(void *arg) {
    int running = 1;
    while (running) {
        RingEntry e;
        mtx_lock(&mtx);
        while (!ring_get(&ring, &e)) {
            cnd_wait(&cnd, &mtx);
        }
        mtx_unlock(&mtx);
        switch (e.type) {
            case BLOCK:
                _db_insert_block(e.p, e.q, e.x, e.y, e.z, e.w);
                break;
            case LIGHT:
                _db_insert_light(e.p, e.q, e.x, e.y, e.z, e.w);
                break;
            case KEY:
                _db_set_key(e.p, e.q, e.key);
                break;
            case COMMIT:
                _db_commit();
                break;
            case EXIT:
                running = 0;
                break;
        }
    }
    return 0;
}