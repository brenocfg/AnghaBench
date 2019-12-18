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
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  fragS ;

/* Variables and functions */
 int /*<<< orphan*/  S_SET_NAME (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  notes ; 
 int /*<<< orphan*/  obj_symbol_new_hook (int /*<<< orphan*/ *) ; 
 char* obstack_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  symbol_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_clear_list_pointers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_lastP ; 
 int /*<<< orphan*/  symbol_rootP ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* tc_canonicalize_symbol_name (char*) ; 
 int /*<<< orphan*/  tc_symbol_new_hook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_symbol_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
symbol_locate (symbolS *    symbolP,
	       const char * name,	/* It is copied, the caller can modify.	 */
	       segT	    segment,	/* Segment identifier (SEG_<something>).  */
	       valueT	    valu,	/* Symbol value.  */
	       fragS *	    frag)	/* Associated fragment.	 */
{
  unsigned int name_length;
  char * preserved_copy_of_name;

  name_length = strlen (name) + 1;   /* +1 for \0.  */
  obstack_grow (&notes, name, name_length);
  preserved_copy_of_name = obstack_finish (&notes);

#ifdef tc_canonicalize_symbol_name
  preserved_copy_of_name =
    tc_canonicalize_symbol_name (preserved_copy_of_name);
#endif

  S_SET_NAME (symbolP, preserved_copy_of_name);

  S_SET_SEGMENT (symbolP, segment);
  S_SET_VALUE (symbolP, valu);
  symbol_clear_list_pointers (symbolP);

  symbol_set_frag (symbolP, frag);

  /* Link to end of symbol chain.  */
  {
    extern int symbol_table_frozen;

    if (symbol_table_frozen)
      abort ();
  }

  symbol_append (symbolP, symbol_lastP, & symbol_rootP, & symbol_lastP);

  obj_symbol_new_hook (symbolP);

#ifdef tc_symbol_new_hook
  tc_symbol_new_hook (symbolP);
#endif

#ifdef DEBUG_SYMS
  verify_symbol_chain (symbol_rootP, symbol_lastP);
#endif /* DEBUG_SYMS  */
}