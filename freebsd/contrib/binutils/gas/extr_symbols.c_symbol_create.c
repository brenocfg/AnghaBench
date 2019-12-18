#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
struct TYPE_10__ {int /*<<< orphan*/ * sy_frag; int /*<<< orphan*/ * bsym; } ;
typedef  TYPE_1__ symbolS ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;

/* Variables and functions */
 int /*<<< orphan*/  S_SET_NAME (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_VALUE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/ * bfd_make_empty_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notes ; 
 int /*<<< orphan*/  obj_symbol_new_hook (TYPE_1__*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 char* save_symbol_name (char const*) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  symbol_clear_list_pointers (TYPE_1__*) ; 
 int /*<<< orphan*/  tc_symbol_new_hook (TYPE_1__*) ; 

symbolS *
symbol_create (const char *name, /* It is copied, the caller can destroy/modify.  */
	       segT segment,	/* Segment identifier (SEG_<something>).  */
	       valueT valu,	/* Symbol value.  */
	       fragS *frag	/* Associated fragment.  */)
{
  char *preserved_copy_of_name;
  symbolS *symbolP;

  preserved_copy_of_name = save_symbol_name (name);

  symbolP = (symbolS *) obstack_alloc (&notes, sizeof (symbolS));

  /* symbol must be born in some fixed state.  This seems as good as any.  */
  memset (symbolP, 0, sizeof (symbolS));

  symbolP->bsym = bfd_make_empty_symbol (stdoutput);
  if (symbolP->bsym == NULL)
    as_fatal ("bfd_make_empty_symbol: %s", bfd_errmsg (bfd_get_error ()));
  S_SET_NAME (symbolP, preserved_copy_of_name);

  S_SET_SEGMENT (symbolP, segment);
  S_SET_VALUE (symbolP, valu);
  symbol_clear_list_pointers (symbolP);

  symbolP->sy_frag = frag;

  obj_symbol_new_hook (symbolP);

#ifdef tc_symbol_new_hook
  tc_symbol_new_hook (symbolP);
#endif

  return symbolP;
}