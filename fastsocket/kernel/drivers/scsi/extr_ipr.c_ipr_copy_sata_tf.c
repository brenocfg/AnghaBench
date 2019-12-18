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
struct ipr_ioarcb_ata_regs {int /*<<< orphan*/  ctl; int /*<<< orphan*/  hob_lbah; int /*<<< orphan*/  hob_lbam; int /*<<< orphan*/  hob_lbal; int /*<<< orphan*/  hob_nsect; int /*<<< orphan*/  hob_feature; int /*<<< orphan*/  command; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; int /*<<< orphan*/  feature; } ;
struct ata_taskfile {int /*<<< orphan*/  ctl; int /*<<< orphan*/  hob_lbah; int /*<<< orphan*/  hob_lbam; int /*<<< orphan*/  hob_lbal; int /*<<< orphan*/  hob_nsect; int /*<<< orphan*/  hob_feature; int /*<<< orphan*/  command; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; int /*<<< orphan*/  feature; } ;

/* Variables and functions */

__attribute__((used)) static void ipr_copy_sata_tf(struct ipr_ioarcb_ata_regs *regs,
			     struct ata_taskfile *tf)
{
	regs->feature = tf->feature;
	regs->nsect = tf->nsect;
	regs->lbal = tf->lbal;
	regs->lbam = tf->lbam;
	regs->lbah = tf->lbah;
	regs->device = tf->device;
	regs->command = tf->command;
	regs->hob_feature = tf->hob_feature;
	regs->hob_nsect = tf->hob_nsect;
	regs->hob_lbal = tf->hob_lbal;
	regs->hob_lbam = tf->hob_lbam;
	regs->hob_lbah = tf->hob_lbah;
	regs->ctl = tf->ctl;
}