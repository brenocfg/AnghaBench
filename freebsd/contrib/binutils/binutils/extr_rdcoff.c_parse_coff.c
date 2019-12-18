#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  x_lnno; } ;
struct TYPE_8__ {TYPE_1__ x_lnsz; scalar_t__ x_fsize; } ;
struct TYPE_9__ {TYPE_2__ x_misc; } ;
union internal_auxent {TYPE_3__ x_sym; } ;
struct internal_syment {scalar_t__ n_numaux; int n_sclass; long n_value; int n_type; } ;
struct coff_types {int /*<<< orphan*/ * basic; int /*<<< orphan*/ * slots; } ;
struct coff_symbols {long symcount; long symno; long coff_symno; int /*<<< orphan*/ ** syms; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_10__ {scalar_t__ offset; } ;
struct TYPE_11__ {TYPE_4__ u; int /*<<< orphan*/  line_number; } ;
typedef  TYPE_5__ alent ;

/* Variables and functions */
 TYPE_5__* BFD_SEND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  C_ALIAS 140 
#define  C_BLOCK 139 
#define  C_EFCN 138 
#define  C_EXT 137 
#define  C_EXTDEF 136 
#define  C_FCN 135 
#define  C_FILE 134 
#define  C_HIDDEN 133 
#define  C_LINE 132 
#define  C_STAT 131 
#define  C_ULABEL 130 
#define  C_USTATIC 129 
#define  C_WEAKEXT 128 
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int DECREF (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISFCN (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int T_MAX ; 
 int T_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _get_lineno ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_asymbol_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_get_auxent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union internal_auxent*) ; 
 int /*<<< orphan*/  bfd_coff_get_syment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_syment*) ; 
 long bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_section (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_end_block (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_end_function (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_record_function (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debug_record_line (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debug_set_filename (void*,char const*) ; 
 int /*<<< orphan*/  debug_start_block (void*,scalar_t__) ; 
 int /*<<< orphan*/  external_coff_symbol_p (int) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  parse_coff_symbol (int /*<<< orphan*/ *,struct coff_types*,int /*<<< orphan*/ *,long,struct internal_syment*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_coff_type (int /*<<< orphan*/ *,struct coff_symbols*,struct coff_types*,long,int,union internal_auxent*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

bfd_boolean
parse_coff (bfd *abfd, asymbol **syms, long symcount, void *dhandle)
{
  struct coff_symbols symbols;
  struct coff_types types;
  int i;
  long next_c_file;
  const char *fnname;
  int fnclass;
  int fntype;
  bfd_vma fnend;
  alent *linenos;
  bfd_boolean within_function;
  long this_coff_symno;

  symbols.syms = syms;
  symbols.symcount = symcount;
  symbols.symno = 0;
  symbols.coff_symno = 0;

  types.slots = NULL;
  for (i = 0; i <= T_MAX; i++)
    types.basic[i] = DEBUG_TYPE_NULL;

  next_c_file = -1;
  fnname = NULL;
  fnclass = 0;
  fntype = 0;
  fnend = 0;
  linenos = NULL;
  within_function = FALSE;

  while (symbols.symno < symcount)
    {
      asymbol *sym;
      const char *name;
      struct internal_syment syment;
      union internal_auxent auxent;
      union internal_auxent *paux;
      debug_type type;

      sym = syms[symbols.symno];

      if (! bfd_coff_get_syment (abfd, sym, &syment))
	{
	  non_fatal (_("bfd_coff_get_syment failed: %s"),
		     bfd_errmsg (bfd_get_error ()));
	  return FALSE;
	}

      name = bfd_asymbol_name (sym);

      this_coff_symno = symbols.coff_symno;

      ++symbols.symno;
      symbols.coff_symno += 1 + syment.n_numaux;

      /* We only worry about the first auxent, because that is the
	 only one which is relevant for debugging information.  */
      if (syment.n_numaux == 0)
	paux = NULL;
      else
	{
	  if (! bfd_coff_get_auxent (abfd, sym, 0, &auxent))
	    {
	      non_fatal (_("bfd_coff_get_auxent failed: %s"),
			 bfd_errmsg (bfd_get_error ()));
	      return FALSE;
	    }
	  paux = &auxent;
	}

      if (this_coff_symno == next_c_file && syment.n_sclass != C_FILE)
	{
	  /* The last C_FILE symbol points to the first external
             symbol.  */
	  if (! debug_set_filename (dhandle, "*globals*"))
	    return FALSE;
	}

      switch (syment.n_sclass)
	{
	case C_EFCN:
	case C_EXTDEF:
	case C_ULABEL:
	case C_USTATIC:
	case C_LINE:
	case C_ALIAS:
	case C_HIDDEN:
	  /* Just ignore these classes.  */
	  break;

	case C_FILE:
	  next_c_file = syment.n_value;
	  if (! debug_set_filename (dhandle, name))
	    return FALSE;
	  break;

	case C_STAT:
	  /* Ignore static symbols with a type of T_NULL.  These
             represent section entries.  */
	  if (syment.n_type == T_NULL)
	    break;
	  /* Fall through.  */
	case C_WEAKEXT:
	case C_EXT:
	  if (ISFCN (syment.n_type))
	    {
	      fnname = name;
	      fnclass = syment.n_sclass;
	      fntype = syment.n_type;
	      if (syment.n_numaux > 0)
		fnend = bfd_asymbol_value (sym) + auxent.x_sym.x_misc.x_fsize;
	      else
		fnend = 0;
	      linenos = BFD_SEND (abfd, _get_lineno, (abfd, sym));
	      break;
	    }
	  type = parse_coff_type (abfd, &symbols, &types, this_coff_symno,
				  syment.n_type, paux, TRUE, dhandle);
	  if (type == DEBUG_TYPE_NULL)
	    return FALSE;
	  if (! parse_coff_symbol (abfd, &types, sym, this_coff_symno, &syment,
				   dhandle, type, within_function))
	    return FALSE;
	  break;

	case C_FCN:
	  if (strcmp (name, ".bf") == 0)
	    {
	      if (fnname == NULL)
		{
		  non_fatal (_("%ld: .bf without preceding function"),
			     this_coff_symno);
		  return FALSE;
		}

	      type = parse_coff_type (abfd, &symbols, &types, this_coff_symno,
				      DECREF (fntype), paux, FALSE, dhandle);
	      if (type == DEBUG_TYPE_NULL)
		return FALSE;

	      if (! debug_record_function (dhandle, fnname, type,
					   external_coff_symbol_p (fnclass),
					   bfd_asymbol_value (sym)))
		return FALSE;

	      if (linenos != NULL)
		{
		  int base;
		  bfd_vma addr;

		  if (syment.n_numaux == 0)
		    base = 0;
		  else
		    base = auxent.x_sym.x_misc.x_lnsz.x_lnno - 1;

		  addr = bfd_get_section_vma (abfd, bfd_get_section (sym));

		  ++linenos;

		  while (linenos->line_number != 0)
		    {
		      if (! debug_record_line (dhandle,
					       linenos->line_number + base,
					       linenos->u.offset + addr))
			return FALSE;
		      ++linenos;
		    }
		}

	      fnname = NULL;
	      linenos = NULL;
	      fnclass = 0;
	      fntype = 0;

	      within_function = TRUE;
	    }
	  else if (strcmp (name, ".ef") == 0)
	    {
	      if (! within_function)
		{
		  non_fatal (_("%ld: unexpected .ef\n"), this_coff_symno);
		  return FALSE;
		}

	      if (bfd_asymbol_value (sym) > fnend)
		fnend = bfd_asymbol_value (sym);
	      if (! debug_end_function (dhandle, fnend))
		return FALSE;

	      fnend = 0;
	      within_function = FALSE;
	    }
	  break;

	case C_BLOCK:
	  if (strcmp (name, ".bb") == 0)
	    {
	      if (! debug_start_block (dhandle, bfd_asymbol_value (sym)))
		return FALSE;
	    }
	  else if (strcmp (name, ".eb") == 0)
	    {
	      if (! debug_end_block (dhandle, bfd_asymbol_value (sym)))
		return FALSE;
	    }
	  break;

	default:
	  type = parse_coff_type (abfd, &symbols, &types, this_coff_symno,
				  syment.n_type, paux, TRUE, dhandle);
	  if (type == DEBUG_TYPE_NULL)
	    return FALSE;
	  if (! parse_coff_symbol (abfd, &types, sym, this_coff_symno, &syment,
				   dhandle, type, within_function))
	    return FALSE;
	  break;
	}
    }

  return TRUE;
}