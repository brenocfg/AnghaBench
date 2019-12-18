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
typedef  unsigned long u32 ;
struct idt77252_dev {unsigned long* tst; size_t tst_index; unsigned long tst_size; int /*<<< orphan*/  tst_lock; int /*<<< orphan*/  tst_timer; int /*<<< orphan*/  tst_state; TYPE_1__* soft_tst; } ;
struct TYPE_2__ {int tste; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAR_REG_NOW ; 
 unsigned long TSTE_MASK ; 
 unsigned long TSTE_OPC_JMP ; 
 unsigned long TSTE_OPC_NULL ; 
 int TSTE_PUSH_ACTIVE ; 
 int TSTE_PUSH_IDLE ; 
 int /*<<< orphan*/  TST_SWITCH_PENDING ; 
 int /*<<< orphan*/  TST_SWITCH_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
tst_timer(unsigned long data)
{
	struct idt77252_dev *card = (struct idt77252_dev *)data;
	unsigned long base, idle, jump;
	unsigned long flags;
	u32 pc;
	int e;

	spin_lock_irqsave(&card->tst_lock, flags);

	base = card->tst[card->tst_index];
	idle = card->tst[card->tst_index ^ 1];

	if (test_bit(TST_SWITCH_WAIT, &card->tst_state)) {
		jump = base + card->tst_size - 2;

		pc = readl(SAR_REG_NOW) >> 2;
		if ((pc ^ idle) & ~(card->tst_size - 1)) {
			mod_timer(&card->tst_timer, jiffies + 1);
			goto out;
		}

		clear_bit(TST_SWITCH_WAIT, &card->tst_state);

		card->tst_index ^= 1;
		write_sram(card, jump, TSTE_OPC_JMP | (base << 2));

		base = card->tst[card->tst_index];
		idle = card->tst[card->tst_index ^ 1];

		for (e = 0; e < card->tst_size - 2; e++) {
			if (card->soft_tst[e].tste & TSTE_PUSH_IDLE) {
				write_sram(card, idle + e,
					   card->soft_tst[e].tste & TSTE_MASK);
				card->soft_tst[e].tste &= ~(TSTE_PUSH_IDLE);
			}
		}
	}

	if (test_and_clear_bit(TST_SWITCH_PENDING, &card->tst_state)) {

		for (e = 0; e < card->tst_size - 2; e++) {
			if (card->soft_tst[e].tste & TSTE_PUSH_ACTIVE) {
				write_sram(card, idle + e,
					   card->soft_tst[e].tste & TSTE_MASK);
				card->soft_tst[e].tste &= ~(TSTE_PUSH_ACTIVE);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			}
		}

		jump = base + card->tst_size - 2;

		write_sram(card, jump, TSTE_OPC_NULL);
		set_bit(TST_SWITCH_WAIT, &card->tst_state);

		mod_timer(&card->tst_timer, jiffies + 1);
	}

out:
	spin_unlock_irqrestore(&card->tst_lock, flags);
}