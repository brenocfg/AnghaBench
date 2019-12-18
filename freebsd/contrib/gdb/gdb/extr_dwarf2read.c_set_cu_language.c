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
struct dwarf2_cu {int /*<<< orphan*/  language; int /*<<< orphan*/  language_defn; } ;

/* Variables and functions */
#define  DW_LANG_Ada83 141 
#define  DW_LANG_Ada95 140 
#define  DW_LANG_C 139 
#define  DW_LANG_C89 138 
#define  DW_LANG_C_plus_plus 137 
#define  DW_LANG_Cobol74 136 
#define  DW_LANG_Cobol85 135 
#define  DW_LANG_Fortran77 134 
#define  DW_LANG_Fortran90 133 
#define  DW_LANG_Fortran95 132 
#define  DW_LANG_Java 131 
#define  DW_LANG_Mips_Assembler 130 
#define  DW_LANG_Modula2 129 
#define  DW_LANG_Pascal83 128 
 int /*<<< orphan*/  language_asm ; 
 int /*<<< orphan*/  language_c ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  language_def (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  language_fortran ; 
 int /*<<< orphan*/  language_java ; 
 int /*<<< orphan*/  language_minimal ; 

__attribute__((used)) static void
set_cu_language (unsigned int lang, struct dwarf2_cu *cu)
{
  switch (lang)
    {
    case DW_LANG_C89:
    case DW_LANG_C:
      cu->language = language_c;
      break;
    case DW_LANG_C_plus_plus:
      cu->language = language_cplus;
      break;
    case DW_LANG_Fortran77:
    case DW_LANG_Fortran90:
    case DW_LANG_Fortran95:
      cu->language = language_fortran;
      break;
    case DW_LANG_Mips_Assembler:
      cu->language = language_asm;
      break;
    case DW_LANG_Java:
      cu->language = language_java;
      break;
    case DW_LANG_Ada83:
    case DW_LANG_Ada95:
    case DW_LANG_Cobol74:
    case DW_LANG_Cobol85:
    case DW_LANG_Pascal83:
    case DW_LANG_Modula2:
    default:
      cu->language = language_minimal;
      break;
    }
  cu->language_defn = language_def (cu->language);
}