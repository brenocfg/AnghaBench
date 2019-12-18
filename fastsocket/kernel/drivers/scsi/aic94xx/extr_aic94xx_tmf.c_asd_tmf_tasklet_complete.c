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
struct tasklet_completion_status {scalar_t__ dl_opcode; int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_valid; int /*<<< orphan*/  tmf_state; } ;
struct done_list_struct {scalar_t__ opcode; } ;
struct asd_ascb {int /*<<< orphan*/  completion; int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_valid; struct tasklet_completion_status* uldd_task; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 scalar_t__ TC_SSP_RESP ; 
 int /*<<< orphan*/  asd_ascb_free (struct asd_ascb*) ; 
 int /*<<< orphan*/  asd_get_tmf_resp_tasklet (struct asd_ascb*,struct done_list_struct*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asd_tmf_tasklet_complete(struct asd_ascb *ascb,
				     struct done_list_struct *dl)
{
	struct tasklet_completion_status *tcs;

	if (!del_timer(&ascb->timer))
		return;

	tcs = ascb->uldd_task;
	ASD_DPRINTK("tmf tasklet complete\n");

	tcs->dl_opcode = dl->opcode;

	if (dl->opcode == TC_SSP_RESP) {
		tcs->tmf_state = asd_get_tmf_resp_tasklet(ascb, dl);
		tcs->tag_valid = ascb->tag_valid;
		tcs->tag = ascb->tag;
	}

	complete(ascb->completion);
	asd_ascb_free(ascb);
}