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
#define  DW_LANG_Ada83 167 
#define  DW_LANG_Ada95 166 
#define  DW_LANG_BLISS 165 
#define  DW_LANG_C 164 
#define  DW_LANG_C11 163 
#define  DW_LANG_C89 162 
#define  DW_LANG_C99 161 
#define  DW_LANG_C_plus_plus 160 
#define  DW_LANG_C_plus_plus_03 159 
#define  DW_LANG_C_plus_plus_11 158 
#define  DW_LANG_C_plus_plus_14 157 
#define  DW_LANG_Cobol74 156 
#define  DW_LANG_Cobol85 155 
#define  DW_LANG_D 154 
#define  DW_LANG_Dylan 153 
#define  DW_LANG_Fortran03 152 
#define  DW_LANG_Fortran08 151 
#define  DW_LANG_Fortran77 150 
#define  DW_LANG_Fortran90 149 
#define  DW_LANG_Fortran95 148 
#define  DW_LANG_Go 147 
#define  DW_LANG_Haskell 146 
#define  DW_LANG_Java 145 
#define  DW_LANG_Julia 144 
#define  DW_LANG_Mips_Assembler 143 
#define  DW_LANG_Modula2 142 
#define  DW_LANG_Modula3 141 
#define  DW_LANG_OCaml 140 
#define  DW_LANG_ObjC 139 
#define  DW_LANG_ObjC_plus_plus 138 
#define  DW_LANG_OpenCL 137 
#define  DW_LANG_PLI 136 
#define  DW_LANG_Pascal83 135 
#define  DW_LANG_Python 134 
#define  DW_LANG_RenderScript 133 
#define  DW_LANG_Rust 132 
#define  DW_LANG_Swift 131 
#define  DW_LANG_UPC 130 
#define  DW_LANG_hi_user 129 
#define  DW_LANG_lo_user 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_LANG_name(unsigned lang, const char **s)
{

	assert(s != NULL);

	switch (lang) {
	case DW_LANG_C89:
		*s = "DW_LANG_C89"; break;
	case DW_LANG_C:
		*s = "DW_LANG_C"; break;
	case DW_LANG_Ada83:
		*s = "DW_LANG_Ada83"; break;
	case DW_LANG_C_plus_plus:
		*s = "DW_LANG_C_plus_plus"; break;
	case DW_LANG_Cobol74:
		*s = "DW_LANG_Cobol74"; break;
	case DW_LANG_Cobol85:
		*s = "DW_LANG_Cobol85"; break;
	case DW_LANG_Fortran77:
		*s = "DW_LANG_Fortran77"; break;
	case DW_LANG_Fortran90:
		*s = "DW_LANG_Fortran90"; break;
	case DW_LANG_Pascal83:
		*s = "DW_LANG_Pascal83"; break;
	case DW_LANG_Modula2:
		*s = "DW_LANG_Modula2"; break;
	case DW_LANG_Java:
		*s = "DW_LANG_Java"; break;
	case DW_LANG_C99:
		*s = "DW_LANG_C99"; break;
	case DW_LANG_Ada95:
		*s = "DW_LANG_Ada95"; break;
	case DW_LANG_Fortran95:
		*s = "DW_LANG_Fortran95"; break;
	case DW_LANG_PLI:
		*s = "DW_LANG_PLI"; break;
	case DW_LANG_ObjC:
		*s = "DW_LANG_ObjC"; break;
	case DW_LANG_ObjC_plus_plus:
		*s = "DW_LANG_ObjC_plus_plus"; break;
	case DW_LANG_UPC:
		*s = "DW_LANG_UPC"; break;
	case DW_LANG_D:
		*s = "DW_LANG_D"; break;
	case DW_LANG_Python:
		*s = "DW_LANG_Python"; break;
	case DW_LANG_OpenCL:
		*s = "DW_LANG_OpenCL"; break;
	case DW_LANG_Go:
		*s = "DW_LANG_Go"; break;
	case DW_LANG_Modula3:
		*s = "DW_LANG_Modula3"; break;
	case DW_LANG_Haskell:
		*s = "DW_LANG_Haskell"; break;
	case DW_LANG_C_plus_plus_03:
		*s = "DW_LANG_C_plus_plus_03"; break;
	case DW_LANG_C_plus_plus_11:
		*s = "DW_LANG_C_plus_plus_11"; break;
	case DW_LANG_OCaml:
		*s = "DW_LANG_OCaml"; break;
	case DW_LANG_Rust:
		*s = "DW_LANG_Rust"; break;
	case DW_LANG_C11:
		*s = "DW_LANG_C11"; break;
	case DW_LANG_Swift:
		*s = "DW_LANG_Swift"; break;
	case DW_LANG_Julia:
		*s = "DW_LANG_Julia"; break;
	case DW_LANG_Dylan:
		*s = "DW_LANG_Dylan"; break;
	case DW_LANG_C_plus_plus_14:
		*s = "DW_LANG_C_plus_plus_14"; break;
	case DW_LANG_Fortran03:
		*s = "DW_LANG_Fortran03"; break;
	case DW_LANG_Fortran08:
		*s = "DW_LANG_Fortran08"; break;
	case DW_LANG_RenderScript:
		*s = "DW_LANG_RenderScript"; break;
	case DW_LANG_BLISS:
		*s = "DW_LANG_BLISS"; break;
	case DW_LANG_lo_user:
		*s = "DW_LANG_lo_user"; break;
	case DW_LANG_Mips_Assembler:
		*s = "DW_LANG_Mips_Assembler"; break;
	case DW_LANG_hi_user:
		*s = "DW_LANG_hi_user"; break;
	default:
		return (DW_DLV_NO_ENTRY);
	}

	return (DW_DLV_OK);
}