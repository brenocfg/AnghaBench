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
 int /*<<< orphan*/ * glist ; 
 int glistlen ; 
 int /*<<< orphan*/  print_completer_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_completer_table ()
{
  int x;

  printf ("static const struct ia64_completer_table\ncompleter_table[] = {\n");
  for (x = 0; x < glistlen; x++)
    print_completer_entry (glist[x]);
  printf ("};\n\n");
}