#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rsc {TYPE_1__* ops; } ;
struct imapper {int /*<<< orphan*/  addr; int /*<<< orphan*/  user; int /*<<< orphan*/  slot; } ;
struct TYPE_10__ {int msr; TYPE_2__* ops; } ;
struct daio {TYPE_3__ rscl; } ;
struct dao {struct imapper** imappers; TYPE_5__* mgr; struct daio daio; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* imap_add ) (TYPE_5__*,struct imapper*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* master ) (TYPE_3__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_3__*) ;int /*<<< orphan*/  (* index ) (TYPE_3__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* master ) (struct rsc*) ;int /*<<< orphan*/  (* next_conj ) (struct rsc*) ;int /*<<< orphan*/  (* output_slot ) (struct rsc*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct imapper* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rsc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (struct rsc*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,struct imapper*) ; 
 int /*<<< orphan*/  stub6 (struct rsc*) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub8 (struct rsc*) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*) ; 

__attribute__((used)) static int dao_set_left_input(struct dao *dao, struct rsc *input)
{
	struct imapper *entry;
	struct daio *daio = &dao->daio;
	int i;

	entry = kzalloc((sizeof(*entry) * daio->rscl.msr), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	/* Program master and conjugate resources */
	input->ops->master(input);
	daio->rscl.ops->master(&daio->rscl);
	for (i = 0; i < daio->rscl.msr; i++, entry++) {
		entry->slot = input->ops->output_slot(input);
		entry->user = entry->addr = daio->rscl.ops->index(&daio->rscl);
		dao->mgr->imap_add(dao->mgr, entry);
		dao->imappers[i] = entry;

		input->ops->next_conj(input);
		daio->rscl.ops->next_conj(&daio->rscl);
	}
	input->ops->master(input);
	daio->rscl.ops->master(&daio->rscl);

	return 0;
}