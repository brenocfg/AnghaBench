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
struct dst_state {int /*<<< orphan*/  socket; int /*<<< orphan*/  permissions; struct dst_cmd* data; struct dst_node* node; } ;
struct dst_node {int /*<<< orphan*/  size; } ;
struct dst_cmd {int /*<<< orphan*/  rw; int /*<<< orphan*/  sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_convert_cmd (struct dst_cmd*) ; 
 int dst_data_send_header (int /*<<< orphan*/ ,struct dst_cmd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_state_lock (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_unlock (struct dst_state*) ; 

__attribute__((used)) static int dst_process_cfg(struct dst_state *st)
{
	struct dst_node *n = st->node;
	struct dst_cmd *cmd = st->data;
	int err;

	cmd->sector = n->size;
	cmd->rw = st->permissions;

	dst_convert_cmd(cmd);

	dst_state_lock(st);
	err = dst_data_send_header(st->socket, cmd, sizeof(struct dst_cmd), 0);
	dst_state_unlock(st);

	return err;
}