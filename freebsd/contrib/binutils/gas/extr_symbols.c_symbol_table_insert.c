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
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 char* hash_jam (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_hash ; 
 int /*<<< orphan*/  sy_hash ; 

void
symbol_table_insert (symbolS *symbolP)
{
  register const char *error_string;

  know (symbolP);
  know (S_GET_NAME (symbolP));

  if (LOCAL_SYMBOL_CHECK (symbolP))
    {
      error_string = hash_jam (local_hash, S_GET_NAME (symbolP),
			       (PTR) symbolP);
      if (error_string != NULL)
	as_fatal (_("inserting \"%s\" into symbol table failed: %s"),
		  S_GET_NAME (symbolP), error_string);
      return;
    }

  if ((error_string = hash_jam (sy_hash, S_GET_NAME (symbolP), (PTR) symbolP)))
    {
      as_fatal (_("inserting \"%s\" into symbol table failed: %s"),
		S_GET_NAME (symbolP), error_string);
    }				/* on error  */
}