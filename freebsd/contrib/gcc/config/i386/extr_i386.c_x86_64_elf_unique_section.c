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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {char* (* strip_name_encoding ) (char const*) ;} ;
typedef  int /*<<< orphan*/  DECL_SECTION_NAME ;

/* Variables and functions */
 scalar_t__ CM_MEDIUM ; 
 scalar_t__ CM_MEDIUM_PIC ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ONE_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAVE_COMDAT_GROUP ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
#define  SECCAT_BSS 143 
#define  SECCAT_DATA 142 
#define  SECCAT_DATA_REL 141 
#define  SECCAT_DATA_REL_LOCAL 140 
#define  SECCAT_DATA_REL_RO 139 
#define  SECCAT_DATA_REL_RO_LOCAL 138 
#define  SECCAT_RODATA 137 
#define  SECCAT_RODATA_MERGE_CONST 136 
#define  SECCAT_RODATA_MERGE_STR 135 
#define  SECCAT_RODATA_MERGE_STR_INIT 134 
#define  SECCAT_SBSS 133 
#define  SECCAT_SDATA 132 
#define  SECCAT_SRODATA 131 
#define  SECCAT_TBSS 130 
#define  SECCAT_TDATA 129 
#define  SECCAT_TEXT 128 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  build_string (size_t,char*) ; 
 int categorize_decl_for_section (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  default_unique_section (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ ix86_cmodel ; 
 scalar_t__ ix86_in_large_data_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char* stub1 (char const*) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static void
x86_64_elf_unique_section (tree decl, int reloc)
{
  if ((ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_MEDIUM_PIC)
      && ix86_in_large_data_p (decl))
    {
      const char *prefix = NULL;
      /* We only need to use .gnu.linkonce if we don't have COMDAT groups.  */
      bool one_only = DECL_ONE_ONLY (decl) && !HAVE_COMDAT_GROUP;

      switch (categorize_decl_for_section (decl, reloc))
	{
	case SECCAT_DATA:
	case SECCAT_DATA_REL:
	case SECCAT_DATA_REL_LOCAL:
	case SECCAT_DATA_REL_RO:
	case SECCAT_DATA_REL_RO_LOCAL:
          prefix = one_only ? ".gnu.linkonce.ld." : ".ldata.";
	  break;
	case SECCAT_BSS:
          prefix = one_only ? ".gnu.linkonce.lb." : ".lbss.";
	  break;
	case SECCAT_RODATA:
	case SECCAT_RODATA_MERGE_STR:
	case SECCAT_RODATA_MERGE_STR_INIT:
	case SECCAT_RODATA_MERGE_CONST:
          prefix = one_only ? ".gnu.linkonce.lr." : ".lrodata.";
	  break;
	case SECCAT_SRODATA:
	case SECCAT_SDATA:
	case SECCAT_SBSS:
	  gcc_unreachable ();
	case SECCAT_TEXT:
	case SECCAT_TDATA:
	case SECCAT_TBSS:
	  /* We don't split these for medium model.  Place them into
	     default sections and hope for best.  */
	  break;
	}
      if (prefix)
	{
	  const char *name;
	  size_t nlen, plen;
	  char *string;
	  plen = strlen (prefix);

	  name = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
	  name = targetm.strip_name_encoding (name);
	  nlen = strlen (name);

	  string = alloca (nlen + plen + 1);
	  memcpy (string, prefix, plen);
	  memcpy (string + plen, name, nlen + 1);

	  DECL_SECTION_NAME (decl) = build_string (nlen + plen, string);
	  return;
	}
    }
  default_unique_section (decl, reloc);
}