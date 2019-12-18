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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** bfd_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_symtab (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/ * symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_mark_written (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_rootP ; 
 int symbol_table_frozen ; 

__attribute__((used)) static void
set_symtab (void)
{
  int nsyms;
  asymbol **asympp;
  symbolS *symp;
  bfd_boolean result;

  /* Count symbols.  We can't rely on a count made by the loop in
     write_object_file, because *_frob_file may add a new symbol or
     two.  */
  nsyms = 0;
  for (symp = symbol_rootP; symp; symp = symbol_next (symp))
    nsyms++;

  if (nsyms)
    {
      int i;
      bfd_size_type amt = (bfd_size_type) nsyms * sizeof (asymbol *);

      asympp = bfd_alloc (stdoutput, amt);
      symp = symbol_rootP;
      for (i = 0; i < nsyms; i++, symp = symbol_next (symp))
	{
	  asympp[i] = symbol_get_bfdsym (symp);
	  symbol_mark_written (symp);
	}
    }
  else
    asympp = 0;
  result = bfd_set_symtab (stdoutput, asympp, nsyms);
  assert (result);
  symbol_table_frozen = 1;
}