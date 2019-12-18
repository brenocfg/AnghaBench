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
struct vc_map {int /*<<< orphan*/  flags; int /*<<< orphan*/  class; TYPE_1__* scq; scalar_t__ scd_index; } ;
struct idt77252_dev {int scd_base; scalar_t__ tct_base; struct vc_map** scd2vc; int /*<<< orphan*/  name; struct vc_map** vcs; } ;
struct TYPE_3__ {int scd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAR_REG_TCMDQ ; 
 int /*<<< orphan*/  SCHED_UBR0 ; 
 int TCMDQ_START ; 
 int TCT_FLAG_UBR ; 
 int TCT_UBR ; 
 int /*<<< orphan*/  VCF_IDLE ; 
 TYPE_1__* alloc_scq (struct idt77252_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_scd (struct idt77252_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct vc_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_card_ubr0(struct idt77252_dev *card)
{
	struct vc_map *vc;

	vc = kzalloc(sizeof(struct vc_map), GFP_KERNEL);
	if (!vc) {
		printk("%s: can't alloc vc\n", card->name);
		return -ENOMEM;
	}
	card->vcs[0] = vc;
	vc->class = SCHED_UBR0;

	vc->scq = alloc_scq(card, vc->class);
	if (!vc->scq) {
		printk("%s: can't get SCQ.\n", card->name);
		return -ENOMEM;
	}

	card->scd2vc[0] = vc;
	vc->scd_index = 0;
	vc->scq->scd = card->scd_base;

	fill_scd(card, vc->scq, vc->class);

	write_sram(card, card->tct_base + 0, TCT_UBR | card->scd_base);
	write_sram(card, card->tct_base + 1, 0);
	write_sram(card, card->tct_base + 2, 0);
	write_sram(card, card->tct_base + 3, 0);
	write_sram(card, card->tct_base + 4, 0);
	write_sram(card, card->tct_base + 5, 0);
	write_sram(card, card->tct_base + 6, 0);
	write_sram(card, card->tct_base + 7, TCT_FLAG_UBR);

	clear_bit(VCF_IDLE, &vc->flags);
	writel(TCMDQ_START | 0, SAR_REG_TCMDQ);
	return 0;
}