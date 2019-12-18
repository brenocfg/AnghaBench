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
struct srcimp_mgr {int /*<<< orphan*/  imap_lock; int /*<<< orphan*/  imappers; scalar_t__ init_imap_added; int /*<<< orphan*/  init_imap; } ;
struct imapper {scalar_t__ addr; } ;

/* Variables and functions */
 int input_mapper_add (int /*<<< orphan*/ *,struct imapper*,int /*<<< orphan*/ ,struct srcimp_mgr*) ; 
 int /*<<< orphan*/  input_mapper_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct srcimp_mgr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srcimp_map_op ; 

__attribute__((used)) static int srcimp_imap_add(struct srcimp_mgr *mgr, struct imapper *entry)
{
	unsigned long flags;
	int err;

	spin_lock_irqsave(&mgr->imap_lock, flags);
	if ((0 == entry->addr) && (mgr->init_imap_added)) {
		input_mapper_delete(&mgr->imappers,
				    mgr->init_imap, srcimp_map_op, mgr);
		mgr->init_imap_added = 0;
	}
	err = input_mapper_add(&mgr->imappers, entry, srcimp_map_op, mgr);
	spin_unlock_irqrestore(&mgr->imap_lock, flags);

	return err;
}