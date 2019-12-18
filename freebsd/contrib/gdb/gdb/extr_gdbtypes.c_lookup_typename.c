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
 scalar_t__ LOC_TYPEDEF ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct type* lookup_primitive_typename (char*) ; 
 struct symbol* lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 

struct type *
lookup_typename (char *name, struct block *block, int noerr)
{
  struct symbol *sym;
  struct type *tmp;

  sym = lookup_symbol (name, block, VAR_DOMAIN, 0, (struct symtab **) NULL);
  if (sym == NULL || SYMBOL_CLASS (sym) != LOC_TYPEDEF)
    {
      tmp = lookup_primitive_typename (name);
      if (tmp)
	{
	  return (tmp);
	}
      else if (!tmp && noerr)
	{
	  return (NULL);
	}
      else
	{
	  error ("No type named %s.", name);
	}
    }
  return (SYMBOL_TYPE (sym));
}