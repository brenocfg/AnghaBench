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
struct macio_chip {TYPE_1__* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_mmio_handlers ; 
 int /*<<< orphan*/  pmf_register_driver (TYPE_1__*,int /*<<< orphan*/ *,struct macio_chip*) ; 

__attribute__((used)) static void macio_mmio_init_one(struct macio_chip *macio)
{
	DBG("Installing MMIO functions for macio %s\n",
	    macio->of_node->full_name);

	pmf_register_driver(macio->of_node, &macio_mmio_handlers, macio);
}