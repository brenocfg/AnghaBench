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

/* Variables and functions */
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct type* java_object_type ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct symtab**) ; 

struct type *
get_java_object_type (void)
{
  if (java_object_type == NULL)
    {
      struct symbol *sym;
      sym = lookup_symbol ("java.lang.Object", NULL, STRUCT_DOMAIN,
			   (int *) 0, (struct symtab **) NULL);
      if (sym == NULL)
	error ("cannot find java.lang.Object");
      java_object_type = SYMBOL_TYPE (sym);
    }
  return java_object_type;
}