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
struct bt_mesh_send_cb {int /*<<< orphan*/  (* end ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void send_cb_finalize(const struct bt_mesh_send_cb *cb,
                                    void *cb_data)
{
    if (!cb) {
        return;
    }

    if (cb->start) {
        cb->start(0, 0, cb_data);
    }

    if (cb->end) {
        cb->end(0, cb_data);
    }
}