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
struct sfax_hw {scalar_t__ cfg; int /*<<< orphan*/  aux_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFAX_PCI_RESET_OFF ; 
 int /*<<< orphan*/  SFAX_PCI_RESET_ON ; 
 scalar_t__ TIGER_AUX_DATA ; 
 int /*<<< orphan*/  TIGER_EXTERN_RESET_OFF ; 
 int /*<<< orphan*/  TIGER_EXTERN_RESET_ON ; 
 scalar_t__ TIGER_RESET_ADDR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reset_speedfax(struct sfax_hw *sf)
{

	pr_debug("%s: resetting card\n", sf->name);
	outb(TIGER_EXTERN_RESET_ON, sf->cfg + TIGER_RESET_ADDR);
	outb(SFAX_PCI_RESET_ON, sf->cfg + TIGER_AUX_DATA);
	mdelay(1);
	outb(TIGER_EXTERN_RESET_OFF, sf->cfg + TIGER_RESET_ADDR);
	sf->aux_data = SFAX_PCI_RESET_OFF;
	outb(sf->aux_data, sf->cfg + TIGER_AUX_DATA);
	mdelay(1);
}