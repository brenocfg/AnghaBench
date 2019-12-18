#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct loadable_section {TYPE_1__* section; } ;
struct dwarf2_debug {unsigned int loadable_section_count; struct loadable_section* loadable_sections; } ;
struct TYPE_2__ {scalar_t__ vma; } ;

/* Variables and functions */

__attribute__((used)) static void
unset_sections (struct dwarf2_debug *stash)
{
  unsigned int i;
  struct loadable_section *p;

  i = stash->loadable_section_count;
  p = stash->loadable_sections;
  for (; i > 0; i--, p++)
    p->section->vma = 0;
}