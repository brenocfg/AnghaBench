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
struct ht_irq_msg {int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct ht_irq_cfg {struct ht_irq_msg msg; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,unsigned int,struct ht_irq_msg*) ;scalar_t__ pos; scalar_t__ idx; } ;

/* Variables and functions */
 struct ht_irq_cfg* get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  ht_irq_lock ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,struct ht_irq_msg*) ; 

void write_ht_irq_msg(unsigned int irq, struct ht_irq_msg *msg)
{
	struct ht_irq_cfg *cfg = get_irq_data(irq);
	unsigned long flags;
	spin_lock_irqsave(&ht_irq_lock, flags);
	if (cfg->msg.address_lo != msg->address_lo) {
		pci_write_config_byte(cfg->dev, cfg->pos + 2, cfg->idx);
		pci_write_config_dword(cfg->dev, cfg->pos + 4, msg->address_lo);
	}
	if (cfg->msg.address_hi != msg->address_hi) {
		pci_write_config_byte(cfg->dev, cfg->pos + 2, cfg->idx + 1);
		pci_write_config_dword(cfg->dev, cfg->pos + 4, msg->address_hi);
	}
	if (cfg->update)
		cfg->update(cfg->dev, irq, msg);
	spin_unlock_irqrestore(&ht_irq_lock, flags);
	cfg->msg = *msg;
}