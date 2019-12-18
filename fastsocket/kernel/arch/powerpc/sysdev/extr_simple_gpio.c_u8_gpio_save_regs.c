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
struct u8_gpio_chip {int /*<<< orphan*/  data; } ;
struct of_mm_gpio_chip {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ ) ; 
 struct u8_gpio_chip* to_u8_gpio_chip (struct of_mm_gpio_chip*) ; 

__attribute__((used)) static void u8_gpio_save_regs(struct of_mm_gpio_chip *mm_gc)
{
	struct u8_gpio_chip *u8_gc = to_u8_gpio_chip(mm_gc);

	u8_gc->data = in_8(mm_gc->regs);
}