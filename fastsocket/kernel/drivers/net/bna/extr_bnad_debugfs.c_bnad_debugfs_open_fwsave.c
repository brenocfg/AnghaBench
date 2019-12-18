#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {struct bnad* i_private; } ;
struct file {struct bnad_debug_info* private_data; } ;
struct bnad_debug_info {int buffer_len; struct bnad_debug_info* debug_buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_4__ {TYPE_1__ ioceth; } ;
struct bnad {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;

/* Variables and functions */
 int BFA_STATUS_ENOFSAVE ; 
 int BFA_STATUS_OK ; 
 int BNA_DBG_FWTRC_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bfa_nw_ioc_debug_fwsave (int /*<<< orphan*/ *,struct bnad_debug_info*,int*) ; 
 int /*<<< orphan*/  kfree (struct bnad_debug_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_debugfs_open_fwsave(struct inode *inode, struct file *file)
{
	struct bnad *bnad = inode->i_private;
	struct bnad_debug_info *fw_debug;
	unsigned long flags;
	int rc;

	fw_debug = kzalloc(sizeof(struct bnad_debug_info), GFP_KERNEL);
	if (!fw_debug)
		return -ENOMEM;

	fw_debug->buffer_len = BNA_DBG_FWTRC_LEN;

	fw_debug->debug_buffer = kzalloc(fw_debug->buffer_len, GFP_KERNEL);
	if (!fw_debug->debug_buffer) {
		kfree(fw_debug);
		fw_debug = NULL;
		return -ENOMEM;
	}

	spin_lock_irqsave(&bnad->bna_lock, flags);
	rc = bfa_nw_ioc_debug_fwsave(&bnad->bna.ioceth.ioc,
			fw_debug->debug_buffer,
			&fw_debug->buffer_len);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	if (rc != BFA_STATUS_OK && rc != BFA_STATUS_ENOFSAVE) {
		kfree(fw_debug->debug_buffer);
		fw_debug->debug_buffer = NULL;
		kfree(fw_debug);
		fw_debug = NULL;
		pr_warn("bna %s: Failed to collect fwsave\n",
			pci_name(bnad->pcidev));
		return -ENOMEM;
	}

	file->private_data = fw_debug;

	return 0;
}