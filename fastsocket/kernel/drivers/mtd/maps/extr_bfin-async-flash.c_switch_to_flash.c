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
struct async_state {int /*<<< orphan*/  flash_ambctl1; int /*<<< orphan*/  flash_ambctl0; int /*<<< orphan*/  save_ambctl1; int /*<<< orphan*/  save_ambctl0; int /*<<< orphan*/  enet_flash_pin; int /*<<< orphan*/  irq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bfin_read_EBIU_AMBCTL0 () ; 
 int /*<<< orphan*/  bfin_read_EBIU_AMBCTL1 () ; 
 int /*<<< orphan*/  bfin_write_EBIU_AMBCTL0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_AMBCTL1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_to_flash(struct async_state *state)
{
	local_irq_save(state->irq_flags);

	gpio_set_value(state->enet_flash_pin, 0);

	state->save_ambctl0 = bfin_read_EBIU_AMBCTL0();
	state->save_ambctl1 = bfin_read_EBIU_AMBCTL1();
	bfin_write_EBIU_AMBCTL0(state->flash_ambctl0);
	bfin_write_EBIU_AMBCTL1(state->flash_ambctl1);
	SSYNC();
}