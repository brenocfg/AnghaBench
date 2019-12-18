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
struct symtab_and_line {int line; struct symtab* symtab; } ;
struct symtab {int dummy; } ;

/* Variables and functions */
 struct symtab_and_line get_current_source_symtab_and_line () ; 

__attribute__((used)) static void
initialize_defaults (struct symtab **default_symtab, int *default_line)
{
  if (*default_symtab == 0)
    {
      /* Use whatever we have for the default source line.  We don't use
         get_current_or_default_symtab_and_line as it can recurse and call
	 us back! */
      struct symtab_and_line cursal = 
	get_current_source_symtab_and_line ();
      
      *default_symtab = cursal.symtab;
      *default_line = cursal.line;
    }
}