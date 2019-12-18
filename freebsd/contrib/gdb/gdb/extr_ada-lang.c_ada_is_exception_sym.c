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
struct symbol {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (char*,char*) ; 
 scalar_t__ LOC_BLOCK ; 
 scalar_t__ LOC_CONST ; 
 scalar_t__ LOC_TYPEDEF ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 char* type_name_no_tag (int /*<<< orphan*/ ) ; 

int
ada_is_exception_sym (struct symbol *sym)
{
  char *type_name = type_name_no_tag (SYMBOL_TYPE (sym));

  return (SYMBOL_CLASS (sym) != LOC_TYPEDEF
	  && SYMBOL_CLASS (sym) != LOC_BLOCK
	  && SYMBOL_CLASS (sym) != LOC_CONST
	  && type_name != NULL && DEPRECATED_STREQ (type_name, "exception"));
}