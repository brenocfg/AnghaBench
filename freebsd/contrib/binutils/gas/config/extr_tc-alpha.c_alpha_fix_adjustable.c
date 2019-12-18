#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_4__ {int fx_r_type; int fx_offset; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; int /*<<< orphan*/ * fx_addsy; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
#define  BFD_RELOC_23_PCREL_S2 158 
#define  BFD_RELOC_32 157 
#define  BFD_RELOC_64 156 
#define  BFD_RELOC_ALPHA_BRSGP 155 
#define  BFD_RELOC_ALPHA_CODEADDR 154 
#define  BFD_RELOC_ALPHA_DTPREL16 153 
#define  BFD_RELOC_ALPHA_DTPREL_HI16 152 
#define  BFD_RELOC_ALPHA_DTPREL_LO16 151 
#define  BFD_RELOC_ALPHA_ELF_LITERAL 150 
#define  BFD_RELOC_ALPHA_GOTDTPREL16 149 
#define  BFD_RELOC_ALPHA_GOTTPREL16 148 
#define  BFD_RELOC_ALPHA_GPDISP 147 
#define  BFD_RELOC_ALPHA_GPDISP_HI16 146 
#define  BFD_RELOC_ALPHA_GPDISP_LO16 145 
#define  BFD_RELOC_ALPHA_GPREL_HI16 144 
#define  BFD_RELOC_ALPHA_GPREL_LO16 143 
#define  BFD_RELOC_ALPHA_HINT 142 
#define  BFD_RELOC_ALPHA_LINKAGE 141 
#define  BFD_RELOC_ALPHA_LITERAL 140 
#define  BFD_RELOC_ALPHA_LITUSE 139 
#define  BFD_RELOC_ALPHA_TLSGD 138 
#define  BFD_RELOC_ALPHA_TLSLDM 137 
#define  BFD_RELOC_ALPHA_TPREL16 136 
#define  BFD_RELOC_ALPHA_TPREL_HI16 135 
#define  BFD_RELOC_ALPHA_TPREL_LO16 134 
#define  BFD_RELOC_GPREL16 133 
#define  BFD_RELOC_GPREL32 132 
#define  BFD_RELOC_VTABLE_ENTRY 131 
#define  BFD_RELOC_VTABLE_INHERIT 130 
#define  STO_ALPHA_NOPV 129 
#define  STO_ALPHA_STD_GPLOAD 128 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 int S_GET_OTHER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad_where (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  generic_force_reloc (TYPE_1__*) ; 

int
alpha_fix_adjustable (fixS *f)
{
  /* Are there any relocation types for which we must generate a
     reloc but we can adjust the values contained within it?   */
  switch (f->fx_r_type)
    {
    case BFD_RELOC_ALPHA_GPDISP_HI16:
    case BFD_RELOC_ALPHA_GPDISP_LO16:
    case BFD_RELOC_ALPHA_GPDISP:
      return 0;

    case BFD_RELOC_ALPHA_LITERAL:
    case BFD_RELOC_ALPHA_ELF_LITERAL:
    case BFD_RELOC_ALPHA_LITUSE:
    case BFD_RELOC_ALPHA_LINKAGE:
    case BFD_RELOC_ALPHA_CODEADDR:
      return 1;

    case BFD_RELOC_VTABLE_ENTRY:
    case BFD_RELOC_VTABLE_INHERIT:
      return 0;

    case BFD_RELOC_GPREL16:
    case BFD_RELOC_GPREL32:
    case BFD_RELOC_ALPHA_GPREL_HI16:
    case BFD_RELOC_ALPHA_GPREL_LO16:
    case BFD_RELOC_23_PCREL_S2:
    case BFD_RELOC_32:
    case BFD_RELOC_64:
    case BFD_RELOC_ALPHA_HINT:
      return 1;

    case BFD_RELOC_ALPHA_TLSGD:
    case BFD_RELOC_ALPHA_TLSLDM:
    case BFD_RELOC_ALPHA_GOTDTPREL16:
    case BFD_RELOC_ALPHA_DTPREL_HI16:
    case BFD_RELOC_ALPHA_DTPREL_LO16:
    case BFD_RELOC_ALPHA_DTPREL16:
    case BFD_RELOC_ALPHA_GOTTPREL16:
    case BFD_RELOC_ALPHA_TPREL_HI16:
    case BFD_RELOC_ALPHA_TPREL_LO16:
    case BFD_RELOC_ALPHA_TPREL16:
      /* ??? No idea why we can't return a reference to .tbss+10, but
	 we're preventing this in the other assemblers.  Follow for now.  */
      return 0;

#ifdef OBJ_ELF
    case BFD_RELOC_ALPHA_BRSGP:
      /* If we have a BRSGP reloc to a local symbol, adjust it to BRADDR and
         let it get resolved at assembly time.  */
      {
	symbolS *sym = f->fx_addsy;
	const char *name;
	int offset = 0;

	if (generic_force_reloc (f))
	  return 0;

	switch (S_GET_OTHER (sym) & STO_ALPHA_STD_GPLOAD)
	  {
	  case STO_ALPHA_NOPV:
	    break;
	  case STO_ALPHA_STD_GPLOAD:
	    offset = 8;
	    break;
	  default:
	    if (S_IS_LOCAL (sym))
	      name = "<local>";
	    else
	      name = S_GET_NAME (sym);
	    as_bad_where (f->fx_file, f->fx_line,
		_("!samegp reloc against symbol without .prologue: %s"),
		name);
	    break;
	  }
	f->fx_r_type = BFD_RELOC_23_PCREL_S2;
	f->fx_offset += offset;
	return 1;
      }
#endif

    default:
      return 1;
    }
}