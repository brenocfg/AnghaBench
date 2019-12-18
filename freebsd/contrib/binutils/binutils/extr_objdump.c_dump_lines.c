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
struct print_file_list {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_line (struct print_file_list*,unsigned int) ; 

__attribute__((used)) static void
dump_lines (struct print_file_list *p, unsigned int start, unsigned int end)
{
  if (p->map == NULL)
    return;
  while (start <= end) 
    {
      print_line (p, start);
      start++;
    }
}