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
 unsigned int SECTION_CODE ; 
 unsigned int SECTION_DEBUG ; 
 int /*<<< orphan*/  get_section (char*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 scalar_t__ trampolines_created ; 

void
file_end_indicate_exec_stack (void)
{
  unsigned int flags = SECTION_DEBUG;
  if (trampolines_created)
    flags |= SECTION_CODE;

  switch_to_section (get_section (".note.GNU-stack", flags, NULL));
}