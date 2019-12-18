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
 char const* note_type_unknown (unsigned int) ; 

__attribute__((used)) static const char *
note_type_xen(unsigned int nt)
{
	switch (nt) {
	case 0: return "XEN_ELFNOTE_INFO";
	case 1: return "XEN_ELFNOTE_ENTRY";
	case 2: return "XEN_ELFNOTE_HYPERCALL_PAGE";
	case 3: return "XEN_ELFNOTE_VIRT_BASE";
	case 4: return "XEN_ELFNOTE_PADDR_OFFSET";
	case 5: return "XEN_ELFNOTE_XEN_VERSION";
	case 6: return "XEN_ELFNOTE_GUEST_OS";
	case 7: return "XEN_ELFNOTE_GUEST_VERSION";
	case 8: return "XEN_ELFNOTE_LOADER";
	case 9: return "XEN_ELFNOTE_PAE_MODE";
	case 10: return "XEN_ELFNOTE_FEATURES";
	case 11: return "XEN_ELFNOTE_BSD_SYMTAB";
	case 12: return "XEN_ELFNOTE_HV_START_LOW";
	case 13: return "XEN_ELFNOTE_L1_MFN_VALID";
	case 14: return "XEN_ELFNOTE_SUSPEND_CANCEL";
	case 15: return "XEN_ELFNOTE_INIT_P2M";
	case 16: return "XEN_ELFNOTE_MOD_START_PFN";
	case 17: return "XEN_ELFNOTE_SUPPORTED_FEATURES";
	default: return (note_type_unknown(nt));
	}
}