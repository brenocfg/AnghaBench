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

/* Variables and functions */
 scalar_t__ bfd_is_local_label_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  flag_keep_locals ; 
 scalar_t__ local_symbol_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * md_undefined_symbol (char*) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/ * symbol_find (char const*) ; 
 int /*<<< orphan*/ * symbol_make (char const*) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 int /*<<< orphan*/  zero_address_frag ; 

symbolS *
symbol_find_or_make (const char *name)
{
  register symbolS *symbolP;

  symbolP = symbol_find (name);

  if (symbolP == NULL)
    {
      if (! flag_keep_locals && bfd_is_local_label_name (stdoutput, name))
	{
	  symbolP = md_undefined_symbol ((char *) name);
	  if (symbolP != NULL)
	    return symbolP;

	  symbolP = (symbolS *) local_symbol_make (name, undefined_section,
						   (valueT) 0,
						   &zero_address_frag);
	  return symbolP;
	}

      symbolP = symbol_make (name);

      symbol_table_insert (symbolP);
    }				/* if symbol wasn't found */

  return (symbolP);
}