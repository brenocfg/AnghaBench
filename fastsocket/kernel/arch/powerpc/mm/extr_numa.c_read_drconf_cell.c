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
typedef  int /*<<< orphan*/  u32 ;
struct of_drconf_cell {int /*<<< orphan*/  flags; int /*<<< orphan*/  aa_index; int /*<<< orphan*/  reserved; int /*<<< orphan*/  drc_index; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  n_mem_addr_cells ; 
 int /*<<< orphan*/  read_n_cells (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void read_drconf_cell(struct of_drconf_cell *drmem, const u32 **cellp)
{
	const u32 *cp;

	drmem->base_addr = read_n_cells(n_mem_addr_cells, cellp);

	cp = *cellp;
	drmem->drc_index = cp[0];
	drmem->reserved = cp[1];
	drmem->aa_index = cp[2];
	drmem->flags = cp[3];

	*cellp = cp + 4;
}