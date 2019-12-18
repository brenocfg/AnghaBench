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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
output_get_insn_name (void)
{
  printf ("const char *\n");
  printf ("get_insn_name (int code)\n");
  printf ("{\n");
  printf ("  if (code == NOOP_MOVE_INSN_CODE)\n");
  printf ("    return \"NOOP_MOVE\";\n");
  printf ("  else\n");
  printf ("    return insn_data[code].name;\n");
  printf ("}\n");
}