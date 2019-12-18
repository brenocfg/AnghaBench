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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {int /*<<< orphan*/  section; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_pc_overlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_and_eval_address_1 (char**) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct symtabs_and_lines
decode_indirect (char **argptr)
{
  struct symtabs_and_lines values;
  CORE_ADDR pc;
  
  (*argptr)++;
  pc = parse_and_eval_address_1 (argptr);

  values.sals = (struct symtab_and_line *)
    xmalloc (sizeof (struct symtab_and_line));

  values.nelts = 1;
  values.sals[0] = find_pc_line (pc, 0);
  values.sals[0].pc = pc;
  values.sals[0].section = find_pc_overlay (pc);

  return values;
}