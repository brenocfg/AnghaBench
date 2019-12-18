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
struct dst_state {int /*<<< orphan*/  ctl; } ;
struct dst_node {struct dst_state* state; } ;
struct dst_network_ctl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dst_state*) ; 
 int PTR_ERR (struct dst_state*) ; 
 int dst_request_remote_config (struct dst_state*) ; 
 struct dst_state* dst_state_alloc (struct dst_node*) ; 
 int /*<<< orphan*/  dst_state_exit_connected (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_free (struct dst_state*) ; 
 int dst_state_init_connected (struct dst_state*) ; 
 int dst_state_schedule_receiver (struct dst_state*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dst_network_ctl*,int) ; 

int dst_node_init_connected(struct dst_node *n, struct dst_network_ctl *r)
{
	struct dst_state *st;
	int err = -ENOMEM;

	st = dst_state_alloc(n);
	if (IS_ERR(st)) {
		err = PTR_ERR(st);
		goto err_out_exit;
	}
	memcpy(&st->ctl, r, sizeof(struct dst_network_ctl));

	err = dst_state_init_connected(st);
	if (err)
		goto err_out_free_data;

	err = dst_request_remote_config(st);
	if (err)
		goto err_out_exit_connected;
	n->state = st;

	err = dst_state_schedule_receiver(st);
	if (err)
		goto err_out_exit_connected;

	return 0;

err_out_exit_connected:
	dst_state_exit_connected(st);
err_out_free_data:
	dst_state_free(st);
err_out_exit:
	n->state = NULL;
	return err;
}