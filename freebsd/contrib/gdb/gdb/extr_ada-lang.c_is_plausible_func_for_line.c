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
struct symtab_and_line {int line; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 struct symtab_and_line find_function_start_sal (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_plausible_func_for_line (struct symbol *sym, int line_num)
{
  struct symtab_and_line start_sal;

  if (sym == NULL)
    return 0;

  start_sal = find_function_start_sal (sym, 0);

  return (start_sal.line != 0 && line_num >= start_sal.line);
}