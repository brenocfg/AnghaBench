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
struct type {int dummy; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 char* TYPE_NAME (struct type*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct symbol* lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct type *
lookup_template_type (char *name, struct type *type, struct block *block)
{
  struct symbol *sym;
  char *nam = (char *) alloca (strlen (name) + strlen (TYPE_NAME (type)) + 4);
  strcpy (nam, name);
  strcat (nam, "<");
  strcat (nam, TYPE_NAME (type));
  strcat (nam, " >");		/* FIXME, extra space still introduced in gcc? */

  sym = lookup_symbol (nam, block, VAR_DOMAIN, 0, (struct symtab **) NULL);

  if (sym == NULL)
    {
      error ("No template type named %s.", name);
    }
  if (TYPE_CODE (SYMBOL_TYPE (sym)) != TYPE_CODE_STRUCT)
    {
      error ("This context has class, union or enum %s, not a struct.", name);
    }
  return (SYMBOL_TYPE (sym));
}