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
typedef  size_t u16 ;
struct isci_request {int /*<<< orphan*/  flags; } ;
struct isci_host {size_t task_context_entries; size_t* io_request_sequence; struct isci_request** reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IREQ_ACTIVE ; 
 size_t ISCI_TAG_SEQ (size_t) ; 
 size_t ISCI_TAG_TCI (size_t) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct isci_request *sci_request_by_tag(struct isci_host *ihost, u16 io_tag)
{
	u16 task_index;
	u16 task_sequence;

	task_index = ISCI_TAG_TCI(io_tag);

	if (task_index < ihost->task_context_entries) {
		struct isci_request *ireq = ihost->reqs[task_index];

		if (test_bit(IREQ_ACTIVE, &ireq->flags)) {
			task_sequence = ISCI_TAG_SEQ(io_tag);

			if (task_sequence == ihost->io_request_sequence[task_index])
				return ireq;
		}
	}

	return NULL;
}