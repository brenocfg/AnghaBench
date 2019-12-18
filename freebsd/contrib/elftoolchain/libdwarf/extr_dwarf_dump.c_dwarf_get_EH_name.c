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
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_EH_PE_absptr 142 
#define  DW_EH_PE_aligned 141 
#define  DW_EH_PE_datarel 140 
#define  DW_EH_PE_funcrel 139 
#define  DW_EH_PE_omit 138 
#define  DW_EH_PE_pcrel 137 
#define  DW_EH_PE_sdata2 136 
#define  DW_EH_PE_sdata4 135 
#define  DW_EH_PE_sdata8 134 
#define  DW_EH_PE_sleb128 133 
#define  DW_EH_PE_textrel 132 
#define  DW_EH_PE_udata2 131 
#define  DW_EH_PE_udata4 130 
#define  DW_EH_PE_udata8 129 
#define  DW_EH_PE_uleb128 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_EH_name(unsigned eh, const char **s)
{

	assert(s != NULL);

	switch (eh) {
	case DW_EH_PE_absptr:
		*s = "DW_EH_PE_absptr"; break;
	case DW_EH_PE_uleb128:
		*s = "DW_EH_PE_uleb128"; break;
	case DW_EH_PE_udata2:
		*s = "DW_EH_PE_udata2"; break;
	case DW_EH_PE_udata4:
		*s = "DW_EH_PE_udata4"; break;
	case DW_EH_PE_udata8:
		*s = "DW_EH_PE_udata8"; break;
	case DW_EH_PE_sleb128:
		*s = "DW_EH_PE_sleb128"; break;
	case DW_EH_PE_sdata2:
		*s = "DW_EH_PE_sdata2"; break;
	case DW_EH_PE_sdata4:
		*s = "DW_EH_PE_sdata4"; break;
	case DW_EH_PE_sdata8:
		*s = "DW_EH_PE_sdata8"; break;
	case DW_EH_PE_pcrel:
		*s = "DW_EH_PE_pcrel"; break;
	case DW_EH_PE_textrel:
		*s = "DW_EH_PE_textrel"; break;
	case DW_EH_PE_datarel:
		*s = "DW_EH_PE_datarel"; break;
	case DW_EH_PE_funcrel:
		*s = "DW_EH_PE_funcrel"; break;
	case DW_EH_PE_aligned:
		*s = "DW_EH_PE_aligned"; break;
	case DW_EH_PE_omit:
		*s = "DW_EH_PE_omit"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}