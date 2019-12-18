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
struct sym_hcb {scalar_t__ scriptb0; scalar_t__ scripta0; } ;
struct sym_fw2b_scr {int dummy; } ;
struct sym_fw2a_scr {int /*<<< orphan*/  data_out; int /*<<< orphan*/  data_in; } ;
struct sym_fw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sym_fw_fill_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_fw_setup_bus_addresses (struct sym_hcb*,struct sym_fw*) ; 

__attribute__((used)) static void 
sym_fw2_setup(struct sym_hcb *np, struct sym_fw *fw)
{
	struct sym_fw2a_scr *scripta0;
	struct sym_fw2b_scr *scriptb0;

	scripta0 = (struct sym_fw2a_scr *) np->scripta0;
	scriptb0 = (struct sym_fw2b_scr *) np->scriptb0;

	/*
	 *  Fill variable parts in scripts.
	 */
	sym_fw_fill_data(scripta0->data_in, scripta0->data_out);

	/*
	 *  Setup bus addresses used from the C code..
	 */
	sym_fw_setup_bus_addresses(np, fw);
}