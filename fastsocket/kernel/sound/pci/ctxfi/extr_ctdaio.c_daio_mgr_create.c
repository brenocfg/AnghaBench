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
struct imapper {int /*<<< orphan*/  list; scalar_t__ user; scalar_t__ next; scalar_t__ addr; scalar_t__ slot; } ;
struct hw {int /*<<< orphan*/  (* daio_mgr_commit_write ) (void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_dsb_dai ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* daio_mgr_dsb_dao ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_blk; } ;
struct daio_mgr {int init_imap_added; TYPE_1__ mgr; int /*<<< orphan*/  commit_write; int /*<<< orphan*/  imap_delete; int /*<<< orphan*/  imap_add; int /*<<< orphan*/  daio_disable; int /*<<< orphan*/  daio_enable; int /*<<< orphan*/  put_daio; int /*<<< orphan*/  get_daio; struct imapper* init_imap; int /*<<< orphan*/  imappers; int /*<<< orphan*/  imap_lock; int /*<<< orphan*/  mgr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAIO ; 
 int /*<<< orphan*/  DAIO_RESOURCE_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  daio_imap_add ; 
 int /*<<< orphan*/  daio_imap_delete ; 
 int /*<<< orphan*/  daio_mgr_commit_write ; 
 int /*<<< orphan*/  daio_mgr_dsb_daio ; 
 int /*<<< orphan*/  daio_mgr_enb_daio ; 
 int /*<<< orphan*/  get_daio_rsc ; 
 int /*<<< orphan*/  kfree (struct daio_mgr*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_daio_rsc ; 
 int rsc_mgr_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rsc_mgr_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ) ; 

int daio_mgr_create(void *hw, struct daio_mgr **rdaio_mgr)
{
	int err, i;
	struct daio_mgr *daio_mgr;
	struct imapper *entry;

	*rdaio_mgr = NULL;
	daio_mgr = kzalloc(sizeof(*daio_mgr), GFP_KERNEL);
	if (!daio_mgr)
		return -ENOMEM;

	err = rsc_mgr_init(&daio_mgr->mgr, DAIO, DAIO_RESOURCE_NUM, hw);
	if (err)
		goto error1;

	spin_lock_init(&daio_mgr->mgr_lock);
	spin_lock_init(&daio_mgr->imap_lock);
	INIT_LIST_HEAD(&daio_mgr->imappers);
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		err = -ENOMEM;
		goto error2;
	}
	entry->slot = entry->addr = entry->next = entry->user = 0;
	list_add(&entry->list, &daio_mgr->imappers);
	daio_mgr->init_imap = entry;
	daio_mgr->init_imap_added = 1;

	daio_mgr->get_daio = get_daio_rsc;
	daio_mgr->put_daio = put_daio_rsc;
	daio_mgr->daio_enable = daio_mgr_enb_daio;
	daio_mgr->daio_disable = daio_mgr_dsb_daio;
	daio_mgr->imap_add = daio_imap_add;
	daio_mgr->imap_delete = daio_imap_delete;
	daio_mgr->commit_write = daio_mgr_commit_write;

	for (i = 0; i < 8; i++) {
		((struct hw *)hw)->daio_mgr_dsb_dao(daio_mgr->mgr.ctrl_blk, i);
		((struct hw *)hw)->daio_mgr_dsb_dai(daio_mgr->mgr.ctrl_blk, i);
	}
	((struct hw *)hw)->daio_mgr_commit_write(hw, daio_mgr->mgr.ctrl_blk);

	*rdaio_mgr = daio_mgr;

	return 0;

error2:
	rsc_mgr_uninit(&daio_mgr->mgr);
error1:
	kfree(daio_mgr);
	return err;
}