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
struct probe_trace_point {unsigned long offset; int retprobe; int /*<<< orphan*/ * symbol; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ dwarf_highpc (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int convert_to_trace_point(Dwarf_Die *sp_die, Dwarf_Addr paddr,
				  bool retprobe, struct probe_trace_point *tp)
{
	Dwarf_Addr eaddr, highaddr;
	const char *name;

	/* Copy the name of probe point */
	name = dwarf_diename(sp_die);
	if (name) {
		if (dwarf_entrypc(sp_die, &eaddr) != 0) {
			pr_warning("Failed to get entry address of %s\n",
				   dwarf_diename(sp_die));
			return -ENOENT;
		}
		if (dwarf_highpc(sp_die, &highaddr) != 0) {
			pr_warning("Failed to get end address of %s\n",
				   dwarf_diename(sp_die));
			return -ENOENT;
		}
		if (paddr > highaddr) {
			pr_warning("Offset specified is greater than size of %s\n",
				   dwarf_diename(sp_die));
			return -EINVAL;
		}
		tp->symbol = strdup(name);
		if (tp->symbol == NULL)
			return -ENOMEM;
		tp->offset = (unsigned long)(paddr - eaddr);
	} else
		/* This function has no name. */
		tp->offset = (unsigned long)paddr;

	/* Return probe must be on the head of a subprogram */
	if (retprobe) {
		if (eaddr != paddr) {
			pr_warning("Return probe must be on the head of"
				   " a real function.\n");
			return -EINVAL;
		}
		tp->retprobe = true;
	}

	return 0;
}