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
typedef  int /*<<< orphan*/ * io_rate_update_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/ * io_rate_update_cb ; 
 int /*<<< orphan*/ * io_rate_update_cb_default ; 

void io_rate_update_register(io_rate_update_callback_t io_rate_update_cb_new) {
	if (io_rate_update_cb_new != NULL) {
		io_rate_update_cb = io_rate_update_cb_new;
	} else {
		io_rate_update_cb = io_rate_update_cb_default;
	}
}