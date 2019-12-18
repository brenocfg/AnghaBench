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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  LOC_CONST 129 
#define  LOC_LABEL 128 
 int SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 struct value* value_from_longest (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_from_pointer (struct type*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
const_var_ref (struct symbol *var)
{
  struct type *type = SYMBOL_TYPE (var);

  switch (SYMBOL_CLASS (var))
    {
    case LOC_CONST:
      return value_from_longest (type, (LONGEST) SYMBOL_VALUE (var));

    case LOC_LABEL:
      return value_from_pointer (type, (CORE_ADDR) SYMBOL_VALUE_ADDRESS (var));

    default:
      return 0;
    }
}