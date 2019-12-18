#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct TYPE_2__ {int la_language; } ;

/* Variables and functions */
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_CODE (struct type*) ; 
 int /*<<< orphan*/  TYPE_CODE_BOOL ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct type* builtin_type_bool ; 
 struct type* builtin_type_f_logical_s2 ; 
 struct type* builtin_type_int ; 
 TYPE_1__* current_language ; 
 struct type* java_boolean_type ; 
#define  language_cplus 131 
#define  language_fortran 130 
#define  language_java 129 
#define  language_pascal 128 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct type *
lang_bool_type (void)
{
  struct symbol *sym;
  struct type *type;
  switch (current_language->la_language)
    {
    case language_fortran:
      sym = lookup_symbol ("logical", NULL, VAR_DOMAIN, NULL, NULL);
      if (sym)
	{
	  type = SYMBOL_TYPE (sym);
	  if (type && TYPE_CODE (type) == TYPE_CODE_BOOL)
	    return type;
	}
      return builtin_type_f_logical_s2;
    case language_cplus:
    case language_pascal:
      if (current_language->la_language==language_cplus)
        {sym = lookup_symbol ("bool", NULL, VAR_DOMAIN, NULL, NULL);}
      else
        {sym = lookup_symbol ("boolean", NULL, VAR_DOMAIN, NULL, NULL);}
      if (sym)
	{
	  type = SYMBOL_TYPE (sym);
	  if (type && TYPE_CODE (type) == TYPE_CODE_BOOL)
	    return type;
	}
      return builtin_type_bool;
    case language_java:
      sym = lookup_symbol ("boolean", NULL, VAR_DOMAIN, NULL, NULL);
      if (sym)
	{
	  type = SYMBOL_TYPE (sym);
	  if (type && TYPE_CODE (type) == TYPE_CODE_BOOL)
	    return type;
	}
      return java_boolean_type;
    default:
      return builtin_type_int;
    }
}