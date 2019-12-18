#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hv_util_service {int /*<<< orphan*/  recv_buffer; } ;
struct TYPE_2__ {int active; } ;

/* Variables and functions */
 int cn_add_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_buffer ; 
 int /*<<< orphan*/  vss_cn_callback ; 
 int /*<<< orphan*/  vss_id ; 
 int /*<<< orphan*/  vss_name ; 
 TYPE_1__ vss_transaction ; 

int
hv_vss_init(struct hv_util_service *srv)
{
	int err;

	err = cn_add_callback(&vss_id, vss_name, vss_cn_callback);
	if (err)
		return err;
	recv_buffer = srv->recv_buffer;

	/*
	 * When this driver loads, the user level daemon that
	 * processes the host requests may not yet be running.
	 * Defer processing channel callbacks until the daemon
	 * has registered.
	 */
	vss_transaction.active = true;
	return 0;
}