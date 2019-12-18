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
struct dwarf_section {int dummy; } ;

/* Variables and functions */
 int process_debug_info (struct dwarf_section*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
display_debug_info (struct dwarf_section *section, void *file)
{
  return process_debug_info (section, file, 0);
}