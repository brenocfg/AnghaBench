#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ magic; scalar_t__ sym_index; scalar_t__ string_ptr; scalar_t__ string_table; scalar_t__* table_ptr; scalar_t__ end_string_ptr; TYPE_12__* esym_ptr; TYPE_9__* native_ptr; TYPE_10__** sym_ptr_ptr; TYPE_10__* sym_ptr; int /*<<< orphan*/  abfd; } ;
typedef  TYPE_8__ pe_ILF_vars ;
typedef  int flagword ;
struct TYPE_20__ {long _n_offset; } ;
struct TYPE_21__ {TYPE_3__ _n_n; } ;
struct TYPE_22__ {unsigned short n_sclass; TYPE_4__ _n; int /*<<< orphan*/  n_scnum; } ;
struct TYPE_23__ {TYPE_5__ syment; } ;
struct TYPE_26__ {TYPE_6__ u; } ;
typedef  TYPE_9__ combined_entry_type ;
struct TYPE_24__ {scalar_t__ name; int flags; TYPE_11__* section; int /*<<< orphan*/  the_bfd; } ;
struct TYPE_15__ {TYPE_9__* native; TYPE_7__ symbol; } ;
typedef  TYPE_10__ coff_symbol_type ;
typedef  TYPE_11__* asection_ptr ;
struct TYPE_18__ {int /*<<< orphan*/  e_offset; } ;
struct TYPE_19__ {TYPE_1__ e; } ;
struct TYPE_17__ {unsigned short* e_sclass; int /*<<< orphan*/  e_scnum; TYPE_2__ e; } ;
struct TYPE_16__ {int /*<<< orphan*/  target_index; } ;
typedef  TYPE_12__ SYMENT ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BSF_EXPORT ; 
 int BSF_FUNCTION ; 
 int BSF_GLOBAL ; 
 int BSF_LOCAL ; 
 unsigned short C_EXT ; 
 unsigned short C_STAT ; 
 unsigned short C_THUMBEXT ; 
 unsigned short C_THUMBEXTFUNC ; 
 unsigned short C_THUMBSTAT ; 
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NUM_ILF_SYMS ; 
 scalar_t__ THUMBPEMAGIC ; 
 int /*<<< orphan*/  bfd_und_section ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
pe_ILF_make_a_symbol (pe_ILF_vars *  vars,
		      const char *   prefix,
		      const char *   symbol_name,
		      asection_ptr   section,
		      flagword       extra_flags)
{
  coff_symbol_type * sym;
  combined_entry_type * ent;
  SYMENT * esym;
  unsigned short sclass;

  if (extra_flags & BSF_LOCAL)
    sclass = C_STAT;
  else
    sclass = C_EXT;

#ifdef THUMBPEMAGIC
  if (vars->magic == THUMBPEMAGIC)
    {
      if (extra_flags & BSF_FUNCTION)
	sclass = C_THUMBEXTFUNC;
      else if (extra_flags & BSF_LOCAL)
	sclass = C_THUMBSTAT;
      else
	sclass = C_THUMBEXT;
    }
#endif

  BFD_ASSERT (vars->sym_index < NUM_ILF_SYMS);

  sym = vars->sym_ptr;
  ent = vars->native_ptr;
  esym = vars->esym_ptr;

  /* Copy the symbol's name into the string table.  */
  sprintf (vars->string_ptr, "%s%s", prefix, symbol_name);

  if (section == NULL)
    section = (asection_ptr) & bfd_und_section;

  /* Initialise the external symbol.  */
  H_PUT_32 (vars->abfd, vars->string_ptr - vars->string_table,
	    esym->e.e.e_offset);
  H_PUT_16 (vars->abfd, section->target_index, esym->e_scnum);
  esym->e_sclass[0] = sclass;

  /* The following initialisations are unnecessary - the memory is
     zero initialised.  They are just kept here as reminders.  */

  /* Initialise the internal symbol structure.  */
  ent->u.syment.n_sclass          = sclass;
  ent->u.syment.n_scnum           = section->target_index;
  ent->u.syment._n._n_n._n_offset = (long) sym;

  sym->symbol.the_bfd = vars->abfd;
  sym->symbol.name    = vars->string_ptr;
  sym->symbol.flags   = BSF_EXPORT | BSF_GLOBAL | extra_flags;
  sym->symbol.section = section;
  sym->native         = ent;

  * vars->table_ptr = vars->sym_index;
  * vars->sym_ptr_ptr = sym;

  /* Adjust pointers for the next symbol.  */
  vars->sym_index ++;
  vars->sym_ptr ++;
  vars->sym_ptr_ptr ++;
  vars->table_ptr ++;
  vars->native_ptr ++;
  vars->esym_ptr ++;
  vars->string_ptr += strlen (symbol_name) + strlen (prefix) + 1;

  BFD_ASSERT (vars->string_ptr < vars->end_string_ptr);
}