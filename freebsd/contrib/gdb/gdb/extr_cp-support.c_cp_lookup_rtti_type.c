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
struct block {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOC_TYPEDEF ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_CLASS 129 
#define  TYPE_CODE_NAMESPACE 128 
 struct symbol* lookup_symbol (char const*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

struct type *
cp_lookup_rtti_type (const char *name, struct block *block)
{
  struct symbol * rtti_sym;
  struct type * rtti_type;

  rtti_sym = lookup_symbol (name, block, STRUCT_DOMAIN, NULL, NULL);

  if (rtti_sym == NULL)
    {
      warning ("RTTI symbol not found for class '%s'", name);
      return NULL;
    }

  if (SYMBOL_CLASS (rtti_sym) != LOC_TYPEDEF)
    {
      warning ("RTTI symbol for class '%s' is not a type", name);
      return NULL;
    }

  rtti_type = SYMBOL_TYPE (rtti_sym);

  switch (TYPE_CODE (rtti_type))
    {
    case TYPE_CODE_CLASS:
      break;
    case TYPE_CODE_NAMESPACE:
      /* chastain/2003-11-26: the symbol tables often contain fake
	 symbols for namespaces with the same name as the struct.
	 This warning is an indication of a bug in the lookup order
	 or a bug in the way that the symbol tables are populated.  */
      warning ("RTTI symbol for class '%s' is a namespace", name);
      return NULL;
    default:
      warning ("RTTI symbol for class '%s' has bad type", name);
      return NULL;
    }

  return rtti_type;
}