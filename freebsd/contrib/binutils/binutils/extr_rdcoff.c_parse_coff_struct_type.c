#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x_size; } ;
struct TYPE_11__ {TYPE_4__ x_lnsz; } ;
struct TYPE_7__ {long l; } ;
struct TYPE_8__ {TYPE_1__ x_endndx; } ;
struct TYPE_9__ {TYPE_2__ x_fcn; } ;
struct TYPE_12__ {TYPE_5__ x_misc; TYPE_3__ x_fcnary; } ;
union internal_auxent {TYPE_6__ x_sym; } ;
struct internal_syment {scalar_t__ n_numaux; int n_sclass; int /*<<< orphan*/  n_type; } ;
struct coff_types {int dummy; } ;
struct coff_symbols {long coff_symno; scalar_t__ symno; scalar_t__ symcount; int /*<<< orphan*/ ** syms; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  scalar_t__ debug_field ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
#define  C_EOS 131 
#define  C_FIELD 130 
#define  C_MOS 129 
#define  C_MOU 128 
 scalar_t__ DEBUG_FIELD_NULL ; 
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  DEBUG_VISIBILITY_PUBLIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int T_STRUCT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int bfd_asymbol_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_get_auxent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union internal_auxent*) ; 
 int /*<<< orphan*/  bfd_coff_get_syment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_syment*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 scalar_t__ debug_make_field (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_make_struct_type (void*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_coff_type (int /*<<< orphan*/ *,struct coff_symbols*,struct coff_types*,long,int /*<<< orphan*/ ,union internal_auxent*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (scalar_t__*,int) ; 

__attribute__((used)) static debug_type
parse_coff_struct_type (bfd *abfd, struct coff_symbols *symbols,
			struct coff_types *types, int ntype,
			union internal_auxent *pauxent, void *dhandle)
{
  long symend;
  int alloc;
  debug_field *fields;
  int count;
  bfd_boolean done;

  symend = pauxent->x_sym.x_fcnary.x_fcn.x_endndx.l;

  alloc = 10;
  fields = (debug_field *) xmalloc (alloc * sizeof *fields);
  count = 0;

  done = FALSE;
  while (! done
	 && symbols->coff_symno < symend
	 && symbols->symno < symbols->symcount)
    {
      asymbol *sym;
      long this_coff_symno;
      struct internal_syment syment;
      union internal_auxent auxent;
      union internal_auxent *psubaux;
      bfd_vma bitpos = 0, bitsize = 0;

      sym = symbols->syms[symbols->symno];

      if (! bfd_coff_get_syment (abfd, sym, &syment))
	{
	  non_fatal (_("bfd_coff_get_syment failed: %s"),
		     bfd_errmsg (bfd_get_error ()));
	  return DEBUG_TYPE_NULL;
	}

      this_coff_symno = symbols->coff_symno;

      ++symbols->symno;
      symbols->coff_symno += 1 + syment.n_numaux;

      if (syment.n_numaux == 0)
	psubaux = NULL;
      else
	{
	  if (! bfd_coff_get_auxent (abfd, sym, 0, &auxent))
	    {
	      non_fatal (_("bfd_coff_get_auxent failed: %s"),
			 bfd_errmsg (bfd_get_error ()));
	      return DEBUG_TYPE_NULL;
	    }
	  psubaux = &auxent;
	}

      switch (syment.n_sclass)
	{
	case C_MOS:
	case C_MOU:
	  bitpos = 8 * bfd_asymbol_value (sym);
	  bitsize = 0;
	  break;

	case C_FIELD:
	  bitpos = bfd_asymbol_value (sym);
	  bitsize = auxent.x_sym.x_misc.x_lnsz.x_size;
	  break;

	case C_EOS:
	  done = TRUE;
	  break;
	}

      if (! done)
	{
	  debug_type ftype;
	  debug_field f;

	  ftype = parse_coff_type (abfd, symbols, types, this_coff_symno,
				   syment.n_type, psubaux, TRUE, dhandle);
	  f = debug_make_field (dhandle, bfd_asymbol_name (sym), ftype,
				bitpos, bitsize, DEBUG_VISIBILITY_PUBLIC);
	  if (f == DEBUG_FIELD_NULL)
	    return DEBUG_TYPE_NULL;

	  if (count + 1 >= alloc)
	    {
	      alloc += 10;
	      fields = ((debug_field *)
			xrealloc (fields, alloc * sizeof *fields));
	    }

	  fields[count] = f;
	  ++count;
	}
    }

  fields[count] = DEBUG_FIELD_NULL;

  return debug_make_struct_type (dhandle, ntype == T_STRUCT,
				 pauxent->x_sym.x_misc.x_lnsz.x_size,
				 fields);
}