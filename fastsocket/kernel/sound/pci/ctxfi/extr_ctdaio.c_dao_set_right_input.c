#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rsc {TYPE_2__* ops; } ;
struct imapper {int /*<<< orphan*/  addr; int /*<<< orphan*/  user; int /*<<< orphan*/  slot; } ;
struct TYPE_12__ {int msr; TYPE_3__* ops; } ;
struct TYPE_9__ {int msr; } ;
struct daio {TYPE_4__ rscr; TYPE_1__ rscl; } ;
struct dao {struct imapper** imappers; TYPE_6__* mgr; struct daio daio; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* imap_add ) (TYPE_6__*,struct imapper*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* master ) (TYPE_4__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_4__*) ;int /*<<< orphan*/  (* index ) (TYPE_4__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* master ) (struct rsc*) ;int /*<<< orphan*/  (* next_conj ) (struct rsc*) ;int /*<<< orphan*/  (* output_slot ) (struct rsc*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct imapper* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rsc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (struct rsc*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,struct imapper*) ; 
 int /*<<< orphan*/  stub6 (struct rsc*) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub8 (struct rsc*) ; 
 int /*<<< orphan*/  stub9 (TYPE_4__*) ; 

__attribute__((used)) static int dao_set_right_input(struct dao *dao, struct rsc *input)
{
	struct imapper *entry;
	struct daio *daio = &dao->daio;
	int i;

	entry = kzalloc((sizeof(*entry) * daio->rscr.msr), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	/* Program master and conjugate resources */
	input->ops->master(input);
	daio->rscr.ops->master(&daio->rscr);
	for (i = 0; i < daio->rscr.msr; i++, entry++) {
		entry->slot = input->ops->output_slot(input);
		entry->user = entry->addr = daio->rscr.ops->index(&daio->rscr);
		dao->mgr->imap_add(dao->mgr, entry);
		dao->imappers[daio->rscl.msr + i] = entry;

		input->ops->next_conj(input);
		daio->rscr.ops->next_conj(&daio->rscr);
	}
	input->ops->master(input);
	daio->rscr.ops->master(&daio->rscr);

	return 0;
}