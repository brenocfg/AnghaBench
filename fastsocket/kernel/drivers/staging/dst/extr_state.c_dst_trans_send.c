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
struct dst_trans {int /*<<< orphan*/  cmd; struct bio* bio; TYPE_1__* n; } ;
struct dst_state {int /*<<< orphan*/  socket; } ;
struct dst_cmd {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct dst_state* state; } ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  dst_convert_cmd (int /*<<< orphan*/ *) ; 
 int dst_data_send_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dst_send_bio (struct dst_state*,int /*<<< orphan*/ *,struct bio*) ; 
 int dst_state_init_connected (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_lock (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_reset_nolock (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_unlock (struct dst_state*) ; 

int dst_trans_send(struct dst_trans *t)
{
	int err;
	struct dst_state *st = t->n->state;
	struct bio *bio = t->bio;

	dst_convert_cmd(&t->cmd);

	dst_state_lock(st);
	if (!st->socket) {
		err = dst_state_init_connected(st);
		if (err)
			goto err_out_unlock;
	}

	if (bio_data_dir(bio) == WRITE) {
		err = dst_send_bio(st, &t->cmd, t->bio);
	} else {
		err = dst_data_send_header(st->socket, &t->cmd,
				sizeof(struct dst_cmd), 0);
	}
	if (err)
		goto err_out_reset;

	dst_state_unlock(st);
	return 0;

err_out_reset:
	dst_state_reset_nolock(st);
err_out_unlock:
	dst_state_unlock(st);

	return err;
}