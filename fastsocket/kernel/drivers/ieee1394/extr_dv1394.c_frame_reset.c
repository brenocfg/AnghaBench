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
struct frame {int /*<<< orphan*/ * frame_end_branch; int /*<<< orphan*/ * frame_end_timestamp; int /*<<< orphan*/ * mid_frame_timestamp; int /*<<< orphan*/ * cip_syt2; int /*<<< orphan*/ * cip_syt1; scalar_t__ assigned_timestamp; int /*<<< orphan*/ * frame_begin_timestamp; scalar_t__ n_packets; scalar_t__ done; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAME_CLEAR ; 

__attribute__((used)) static void frame_reset(struct frame *f)
{
	f->state = FRAME_CLEAR;
	f->done = 0;
	f->n_packets = 0;
	f->frame_begin_timestamp = NULL;
	f->assigned_timestamp = 0;
	f->cip_syt1 = NULL;
	f->cip_syt2 = NULL;
	f->mid_frame_timestamp = NULL;
	f->frame_end_timestamp = NULL;
	f->frame_end_branch = NULL;
}