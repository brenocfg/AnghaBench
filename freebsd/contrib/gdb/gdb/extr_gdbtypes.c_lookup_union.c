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
 scalar_t__ DECLARED_TYPE_UNION ; 
 scalar_t__ HAVE_CPLUS_STRUCT (struct type*) ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_UNION ; 
 scalar_t__ TYPE_DECLARED_TYPE (struct type*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct symbol* lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 

struct type *
lookup_union (char *name, struct block *block)
{
  struct symbol *sym;
  struct type *t;

  sym = lookup_symbol (name, block, STRUCT_DOMAIN, 0,
		       (struct symtab **) NULL);

  if (sym == NULL)
    error ("No union type named %s.", name);

  t = SYMBOL_TYPE (sym);

  if (TYPE_CODE (t) == TYPE_CODE_UNION)
    return (t);

  /* C++ unions may come out with TYPE_CODE_CLASS, but we look at
   * a further "declared_type" field to discover it is really a union.
   */
  if (HAVE_CPLUS_STRUCT (t))
    if (TYPE_DECLARED_TYPE (t) == DECLARED_TYPE_UNION)
      return (t);

  /* If we get here, it's not a union */
  error ("This context has class, struct or enum %s, not a union.", name);
}