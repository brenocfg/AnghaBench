#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct imapper {int dummy; } ;
struct TYPE_4__ {int msr; } ;
struct daio {TYPE_1__ rscl; } ;
struct dao {struct imapper** imappers; TYPE_2__* mgr; struct daio daio; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* imap_delete ) (TYPE_2__*,struct imapper*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct imapper*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct imapper*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,struct imapper*) ; 

__attribute__((used)) static int dao_clear_left_input(struct dao *dao)
{
	struct imapper *entry;
	struct daio *daio = &dao->daio;
	int i;

	if (!dao->imappers[0])
		return 0;

	entry = dao->imappers[0];
	dao->mgr->imap_delete(dao->mgr, entry);
	/* Program conjugate resources */
	for (i = 1; i < daio->rscl.msr; i++) {
		entry = dao->imappers[i];
		dao->mgr->imap_delete(dao->mgr, entry);
		dao->imappers[i] = NULL;
	}

	kfree(dao->imappers[0]);
	dao->imappers[0] = NULL;

	return 0;
}