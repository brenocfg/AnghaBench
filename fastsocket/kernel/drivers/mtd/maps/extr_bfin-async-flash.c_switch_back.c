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
struct async_state {int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  enet_flash_pin; int /*<<< orphan*/  save_ambctl1; int /*<<< orphan*/  save_ambctl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bfin_write_EBIU_AMBCTL0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_AMBCTL1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_back(struct async_state *state)
{
	bfin_write_EBIU_AMBCTL0(state->save_ambctl0);
	bfin_write_EBIU_AMBCTL1(state->save_ambctl1);
	SSYNC();

	gpio_set_value(state->enet_flash_pin, 1);

	local_irq_restore(state->irq_flags);
}