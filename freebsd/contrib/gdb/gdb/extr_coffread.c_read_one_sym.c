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
typedef  union internal_auxent {int dummy; } internal_auxent ;
struct internal_syment {int n_numaux; int n_sclass; scalar_t__ n_type; int /*<<< orphan*/  n_scnum; int /*<<< orphan*/  n_value; } ;
struct coff_symbol {int c_symnum; int c_naux; char* c_name; int c_sclass; unsigned int c_type; int /*<<< orphan*/  c_value; int /*<<< orphan*/  c_secnum; } ;

/* Variables and functions */
#define  C_BLOCK 140 
#define  C_EFCN 139 
#define  C_EXT 138 
#define  C_FCN 137 
#define  C_LABEL 136 
#define  C_NT_WEAK 135 
#define  C_SECTION 134 
#define  C_STAT 133 
#define  C_THUMBEXT 132 
#define  C_THUMBEXTFUNC 131 
#define  C_THUMBLABEL 130 
#define  C_THUMBSTAT 129 
#define  C_THUMBSTATFUNC 128 
 int /*<<< orphan*/  SDB_TYPE (unsigned int) ; 
 int /*<<< orphan*/  bfd_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_coff_swap_aux_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  bfd_coff_swap_sym_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cs_section_address (struct coff_symbol*,int /*<<< orphan*/ ) ; 
 char* getsymname (struct internal_syment*) ; 
 int /*<<< orphan*/  local_auxesz ; 
 int /*<<< orphan*/  local_symesz ; 
 int /*<<< orphan*/  nlist_bfd_global ; 
 scalar_t__ pe_file ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  symfile_bfd ; 
 int symnum ; 
 int /*<<< orphan*/  temp_aux ; 
 int /*<<< orphan*/  temp_sym ; 

__attribute__((used)) static void
read_one_sym (struct coff_symbol *cs,
	      struct internal_syment *sym,
	      union internal_auxent *aux)
{
  int i;

  cs->c_symnum = symnum;
  bfd_bread (temp_sym, local_symesz, nlist_bfd_global);
  bfd_coff_swap_sym_in (symfile_bfd, temp_sym, (char *) sym);
  cs->c_naux = sym->n_numaux & 0xff;
  if (cs->c_naux >= 1)
    {
      bfd_bread (temp_aux, local_auxesz, nlist_bfd_global);
      bfd_coff_swap_aux_in (symfile_bfd, temp_aux, sym->n_type, sym->n_sclass,
			    0, cs->c_naux, (char *) aux);
      /* If more than one aux entry, read past it (only the first aux
         is important). */
      for (i = 1; i < cs->c_naux; i++)
	bfd_bread (temp_aux, local_auxesz, nlist_bfd_global);
    }
  cs->c_name = getsymname (sym);
  cs->c_value = sym->n_value;
  cs->c_sclass = (sym->n_sclass & 0xff);
  cs->c_secnum = sym->n_scnum;
  cs->c_type = (unsigned) sym->n_type;
  if (!SDB_TYPE (cs->c_type))
    cs->c_type = 0;

#if 0
  if (cs->c_sclass & 128)
    printf ("thumb symbol %s, class 0x%x\n", cs->c_name, cs->c_sclass);
#endif

  symnum += 1 + cs->c_naux;

  /* The PE file format stores symbol values as offsets within the
     section, rather than as absolute addresses.  We correct that
     here, if the symbol has an appropriate storage class.  FIXME: We
     should use BFD to read the symbols, rather than duplicating the
     work here.  */
  if (pe_file)
    {
      switch (cs->c_sclass)
	{
	case C_EXT:
	case C_THUMBEXT:
	case C_THUMBEXTFUNC:
	case C_SECTION:
	case C_NT_WEAK:
	case C_STAT:
	case C_THUMBSTAT:
	case C_THUMBSTATFUNC:
	case C_LABEL:
	case C_THUMBLABEL:
	case C_BLOCK:
	case C_FCN:
	case C_EFCN:
	  if (cs->c_secnum != 0)
	    cs->c_value += cs_section_address (cs, symfile_bfd);
	  break;
	}
    }
}