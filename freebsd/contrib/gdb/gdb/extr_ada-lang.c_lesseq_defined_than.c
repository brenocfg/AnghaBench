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
 int /*<<< orphan*/  DEPRECATED_STREQN (char*,char*,int) ; 
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
#define  LOC_CONST 130 
#define  LOC_TYPEDEF 129 
#define  LOC_UNDEF 128 
 int SYMBOL_CLASS (struct symbol*) ; 
 scalar_t__ SYMBOL_DOMAIN (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_CODE (struct type*) ; 
 int /*<<< orphan*/  equiv_types (struct type*,struct type*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
lesseq_defined_than (struct symbol *sym0, struct symbol *sym1)
{
  if (sym0 == sym1)
    return 1;
  if (SYMBOL_DOMAIN (sym0) != SYMBOL_DOMAIN (sym1)
      || SYMBOL_CLASS (sym0) != SYMBOL_CLASS (sym1))
    return 0;

  switch (SYMBOL_CLASS (sym0))
    {
    case LOC_UNDEF:
      return 1;
    case LOC_TYPEDEF:
      {
	struct type *type0 = SYMBOL_TYPE (sym0);
	struct type *type1 = SYMBOL_TYPE (sym1);
	char *name0 = DEPRECATED_SYMBOL_NAME (sym0);
	char *name1 = DEPRECATED_SYMBOL_NAME (sym1);
	int len0 = strlen (name0);
	return
	  TYPE_CODE (type0) == TYPE_CODE (type1)
	  && (equiv_types (type0, type1)
	      || (len0 < strlen (name1) && DEPRECATED_STREQN (name0, name1, len0)
		  && DEPRECATED_STREQN (name1 + len0, "___XV", 5)));
      }
    case LOC_CONST:
      return SYMBOL_VALUE (sym0) == SYMBOL_VALUE (sym1)
	&& equiv_types (SYMBOL_TYPE (sym0), SYMBOL_TYPE (sym1));
    default:
      return 0;
    }
}