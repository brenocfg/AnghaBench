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
typedef  int /*<<< orphan*/  sctp_cmd_t ;
struct TYPE_3__ {scalar_t__ next_cmd; scalar_t__ next_free_slot; int /*<<< orphan*/ * cmds; } ;
typedef  TYPE_1__ sctp_cmd_seq_t ;

/* Variables and functions */

sctp_cmd_t *sctp_next_cmd(sctp_cmd_seq_t *seq)
{
	sctp_cmd_t *retval = NULL;

	if (seq->next_cmd < seq->next_free_slot)
		retval = &seq->cmds[seq->next_cmd++];

	return retval;
}