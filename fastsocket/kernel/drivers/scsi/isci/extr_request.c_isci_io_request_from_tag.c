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
typedef  int /*<<< orphan*/  u16 ;
struct sas_task {struct isci_request* lldd_task; } ;
struct TYPE_2__ {struct sas_task* io_task_ptr; } ;
struct isci_request {int /*<<< orphan*/  flags; TYPE_1__ ttype_ptr; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IREQ_TMF ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct isci_request* isci_request_from_tag (struct isci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct isci_request *isci_io_request_from_tag(struct isci_host *ihost,
						     struct sas_task *task,
						     u16 tag)
{
	struct isci_request *ireq;

	ireq = isci_request_from_tag(ihost, tag);
	ireq->ttype_ptr.io_task_ptr = task;
	clear_bit(IREQ_TMF, &ireq->flags);
	task->lldd_task = ireq;

	return ireq;
}