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
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  gen_offset (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_sym_offset (struct agent_expr *ax, struct symbol *var)
{
  gen_offset (ax, SYMBOL_VALUE (var));
}