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
struct symbol {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOC_TYPEDEF ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct symbol* standard_lookup (char const*,int /*<<< orphan*/ ) ; 

struct type *
ada_find_any_type (const char *name)
{
  struct symbol *sym;

  sym = standard_lookup (name, VAR_DOMAIN);
  if (sym != NULL && SYMBOL_CLASS (sym) == LOC_TYPEDEF)
    return SYMBOL_TYPE (sym);

  sym = standard_lookup (name, STRUCT_DOMAIN);
  if (sym != NULL)
    return SYMBOL_TYPE (sym);

  return NULL;
}