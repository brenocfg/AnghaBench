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
typedef  int /*<<< orphan*/  macro_entry ;

/* Variables and functions */
 char TOLOWER (char const) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_macro (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_jam (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macro_hash ; 
 size_t strlen (char const*) ; 

void
delete_macro (const char *name)
{
  char *copy;
  size_t i, len;
  macro_entry *macro;

  len = strlen (name);
  copy = (char *) alloca (len + 1);
  for (i = 0; i < len; ++i)
    copy[i] = TOLOWER (name[i]);
  copy[i] = '\0';

  /* Since hash_delete doesn't free memory, just clear out the entry.  */
  if ((macro = hash_find (macro_hash, copy)) != NULL)
    {
      hash_jam (macro_hash, copy, NULL);
      free_macro (macro);
    }
  else
    as_warn (_("Attempt to purge non-existant macro `%s'"), copy);
}