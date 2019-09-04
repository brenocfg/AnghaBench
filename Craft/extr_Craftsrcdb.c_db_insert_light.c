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
 int /*<<< orphan*/  cnd_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring ; 
 int /*<<< orphan*/  ring_put_light (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

void db_insert_light(int p, int q, int x, int y, int z, int w) {
    if (!db_enabled) {
        return;
    }
    mtx_lock(&mtx);
    ring_put_light(&ring, p, q, x, y, z, w);
    cnd_signal(&cnd);
    mtx_unlock(&mtx);
}