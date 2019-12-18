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
struct reg_entry {int number; int type; char const* name; int /*<<< orphan*/ * neon; scalar_t__ builtin; } ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arm_reg_hsh ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*) ; 
 struct reg_entry* hash_find (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hash_insert (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct reg_entry* xmalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static struct reg_entry *
insert_reg_alias (char *str, int number, int type)
{
  struct reg_entry *new;
  const char *name;

  if ((new = hash_find (arm_reg_hsh, str)) != 0)
    {
      if (new->builtin)
	as_warn (_("ignoring attempt to redefine built-in register '%s'"), str);

      /* Only warn about a redefinition if it's not defined as the
	 same register.	 */
      else if (new->number != number || new->type != type)
	as_warn (_("ignoring redefinition of register alias '%s'"), str);

      return 0;
    }

  name = xstrdup (str);
  new = xmalloc (sizeof (struct reg_entry));

  new->name = name;
  new->number = number;
  new->type = type;
  new->builtin = FALSE;
  new->neon = NULL;

  if (hash_insert (arm_reg_hsh, name, (PTR) new))
    abort ();
  
  return new;
}