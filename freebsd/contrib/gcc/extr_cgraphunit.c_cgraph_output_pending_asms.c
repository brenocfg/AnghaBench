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
struct cgraph_asm_node {int /*<<< orphan*/  asm_str; struct cgraph_asm_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assemble_asm (int /*<<< orphan*/ ) ; 
 struct cgraph_asm_node* cgraph_asm_nodes ; 
 scalar_t__ errorcount ; 
 scalar_t__ sorrycount ; 

__attribute__((used)) static void
cgraph_output_pending_asms (void)
{
  struct cgraph_asm_node *can;

  if (errorcount || sorrycount)
    return;

  for (can = cgraph_asm_nodes; can; can = can->next)
    assemble_asm (can->asm_str);
  cgraph_asm_nodes = NULL;
}