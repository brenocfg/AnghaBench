#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct elf_obj_sy {int /*<<< orphan*/ * versioned_name; TYPE_4__* size; } ;
struct TYPE_7__ {int X_op; scalar_t__ X_add_number; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/ * X_op_symbol; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ fr_address; } ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 int BSF_OBJECT ; 
 scalar_t__ ECOFF_DEBUGGING ; 
 char ELF_VER_CHR ; 
#define  O_constant 129 
#define  O_subtract 128 
 int /*<<< orphan*/ * S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_GET_OTHER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_COMMON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_WEAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_NAME (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_OTHER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_SIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_WEAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TARGET_OS ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  copy_symbol_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecoff_frob_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* strchr (int /*<<< orphan*/ *,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * symbol_find_or_make (int /*<<< orphan*/ *) ; 
 TYPE_3__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 TYPE_1__* symbol_get_frag (int /*<<< orphan*/ *) ; 
 struct elf_obj_sy* symbol_get_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
elf_frob_symbol (symbolS *symp, int *puntp)
{
  struct elf_obj_sy *sy_obj;

#ifdef NEED_ECOFF_DEBUG
  if (ECOFF_DEBUGGING)
    ecoff_frob_symbol (symp);
#endif

  sy_obj = symbol_get_obj (symp);

  if (sy_obj->size != NULL)
    {
      switch (sy_obj->size->X_op)
	{
	case O_subtract:
	  S_SET_SIZE (symp,
		      (S_GET_VALUE (sy_obj->size->X_add_symbol)
		       + sy_obj->size->X_add_number
		       - S_GET_VALUE (sy_obj->size->X_op_symbol)));
	  break;
	case O_constant:
	  S_SET_SIZE (symp,
		      (S_GET_VALUE (sy_obj->size->X_add_symbol)
		       + sy_obj->size->X_add_number));
	  break;
	default:
	  as_bad (_(".size expression too complicated to fix up"));
	  break;
	}
      free (sy_obj->size);
      sy_obj->size = NULL;
    }

  if (sy_obj->versioned_name != NULL)
    {
      char *p;

      p = strchr (sy_obj->versioned_name, ELF_VER_CHR);
      know (p != NULL);

      /* This symbol was given a new name with the .symver directive.

	 If this is an external reference, just rename the symbol to
	 include the version string.  This will make the relocs be
	 against the correct versioned symbol.

	 If this is a definition, add an alias.  FIXME: Using an alias
	 will permit the debugging information to refer to the right
	 symbol.  However, it's not clear whether it is the best
	 approach.  */

      if (! S_IS_DEFINED (symp))
	{
	  /* Verify that the name isn't using the @@ syntax--this is
	     reserved for definitions of the default version to link
	     against.  */
	  if (p[1] == ELF_VER_CHR)
	    {
	      as_bad (_("invalid attempt to declare external version name as default in symbol `%s'"),
		      sy_obj->versioned_name);
	      *puntp = TRUE;
	    }
	  S_SET_NAME (symp, sy_obj->versioned_name);
	}
      else
	{
	  if (p[1] == ELF_VER_CHR && p[2] == ELF_VER_CHR)
	    {
	      size_t l;

	      /* The @@@ syntax is a special case. It renames the
		 symbol name to versioned_name with one `@' removed.  */
	      l = strlen (&p[3]) + 1;
	      memmove (&p[2], &p[3], l);
	      S_SET_NAME (symp, sy_obj->versioned_name);
	    }
	  else
	    {
	      symbolS *symp2;

	      /* FIXME: Creating a new symbol here is risky.  We're
		 in the final loop over the symbol table.  We can
		 get away with it only because the symbol goes to
		 the end of the list, where the loop will still see
		 it.  It would probably be better to do this in
		 obj_frob_file_before_adjust.  */

	      symp2 = symbol_find_or_make (sy_obj->versioned_name);

	      /* Now we act as though we saw symp2 = sym.  */

	      S_SET_SEGMENT (symp2, S_GET_SEGMENT (symp));

	      /* Subtracting out the frag address here is a hack
		 because we are in the middle of the final loop.  */
	      S_SET_VALUE (symp2,
			   (S_GET_VALUE (symp)
			    - symbol_get_frag (symp)->fr_address));

	      symbol_set_frag (symp2, symbol_get_frag (symp));

	      /* This will copy over the size information.  */
	      copy_symbol_attributes (symp2, symp);

	      S_SET_OTHER (symp2, S_GET_OTHER (symp));

	      if (S_IS_WEAK (symp))
		S_SET_WEAK (symp2);

	      if (S_IS_EXTERNAL (symp))
		S_SET_EXTERNAL (symp2);
	    }
	}
    }

  /* Double check weak symbols.  */
  if (S_IS_WEAK (symp))
    {
      if (S_IS_COMMON (symp))
	as_bad (_("symbol `%s' can not be both weak and common"),
		S_GET_NAME (symp));
    }

#ifdef TC_MIPS
  /* The Irix 5 and 6 assemblers set the type of any common symbol and
     any undefined non-function symbol to STT_OBJECT.  We try to be
     compatible, since newer Irix 5 and 6 linkers care.  However, we
     only set undefined symbols to be STT_OBJECT if we are on Irix,
     because that is the only time gcc will generate the necessary
     .global directives to mark functions.  */

  if (S_IS_COMMON (symp))
    symbol_get_bfdsym (symp)->flags |= BSF_OBJECT;

  if (strstr (TARGET_OS, "irix") != NULL
      && ! S_IS_DEFINED (symp)
      && (symbol_get_bfdsym (symp)->flags & BSF_FUNCTION) == 0)
    symbol_get_bfdsym (symp)->flags |= BSF_OBJECT;
#endif
}