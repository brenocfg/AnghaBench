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
struct c67x00_hcd {scalar_t__ current_frame; scalar_t__ last_frame; int /*<<< orphan*/  lock; int /*<<< orphan*/  td_list; int /*<<< orphan*/  sie; int /*<<< orphan*/  urb_count; int /*<<< orphan*/  endpoint_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  c67x00_all_tds_processed (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_check_td_list (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_fill_frame (struct c67x00_hcd*) ; 
 scalar_t__ c67x00_get_current_frame_number (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_ll_hpi_disable_sofeop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c67x00_send_frame (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c67x00_do_work(struct c67x00_hcd *c67x00)
{
	spin_lock(&c67x00->lock);
	/* Make sure all tds are processed */
	if (!c67x00_all_tds_processed(c67x00))
		goto out;

	c67x00_check_td_list(c67x00);

	/* no td's are being processed (current == 0)
	 * and all have been "checked" */
	complete(&c67x00->endpoint_disable);

	if (!list_empty(&c67x00->td_list))
		goto out;

	c67x00->current_frame = c67x00_get_current_frame_number(c67x00);
	if (c67x00->current_frame == c67x00->last_frame)
		goto out;	/* Don't send tds in same frame */
	c67x00->last_frame = c67x00->current_frame;

	/* If no urbs are scheduled, our work is done */
	if (!c67x00->urb_count) {
		c67x00_ll_hpi_disable_sofeop(c67x00->sie);
		goto out;
	}

	c67x00_fill_frame(c67x00);
	if (!list_empty(&c67x00->td_list))
		/* TD's have been added to the frame */
		c67x00_send_frame(c67x00);

 out:
	spin_unlock(&c67x00->lock);
}