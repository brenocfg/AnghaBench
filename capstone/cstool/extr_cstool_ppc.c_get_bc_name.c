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

/* Variables and functions */
#define  PPC_BC_EQ 138 
#define  PPC_BC_GE 137 
#define  PPC_BC_GT 136 
#define  PPC_BC_INVALID 135 
#define  PPC_BC_LE 134 
#define  PPC_BC_LT 133 
#define  PPC_BC_NE 132 
#define  PPC_BC_NS 131 
#define  PPC_BC_NU 130 
#define  PPC_BC_SO 129 
#define  PPC_BC_UN 128 

__attribute__((used)) static const char* get_bc_name(int bc)
{
	switch(bc) {
		default:
		case PPC_BC_INVALID:
			return ("invalid");
		case PPC_BC_LT:
			return ("lt");
		case PPC_BC_LE:
			return ("le");
		case PPC_BC_EQ:
			return ("eq");
		case PPC_BC_GE:
			return ("ge");
		case PPC_BC_GT:
			return ("gt");
		case PPC_BC_NE:
			return ("ne");
		case PPC_BC_UN:
			return ("un");
		case PPC_BC_NU:
			return ("nu");
		case PPC_BC_SO:
			return ("so");
		case PPC_BC_NS:
			return ("ns");
	}
}