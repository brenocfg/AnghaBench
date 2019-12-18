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
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct symbol* lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 

struct type *
lookup_enum (char *name, struct block *block)
{
  struct symbol *sym;

  sym = lookup_symbol (name, block, STRUCT_DOMAIN, 0,
		       (struct symtab **) NULL);
  if (sym == NULL)
    {
      error ("No enum type named %s.", name);
    }
  if (TYPE_CODE (SYMBOL_TYPE (sym)) != TYPE_CODE_ENUM)
    {
      error ("This context has class, struct or union %s, not an enum.", name);
    }
  return (SYMBOL_TYPE (sym));
}