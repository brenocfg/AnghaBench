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
typedef  int uint8_t ;
struct TYPE_3__ {int dbgp_isa; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;

/* Variables and functions */
#define  DW_ISA_ARM 130 
#define  DW_ISA_X86 129 
#define  DW_ISA_X86_64 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
_dwarf_get_minlen(Dwarf_P_Debug dbg)
{

	assert(dbg != NULL);

	switch (dbg->dbgp_isa) {
	case DW_ISA_ARM:
		return (2);
	case DW_ISA_X86:
	case DW_ISA_X86_64:
		return (1);
	default:
		return (4);
	}
}