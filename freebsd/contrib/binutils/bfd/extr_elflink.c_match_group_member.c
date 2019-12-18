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
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ bfd_elf_match_symbols_in_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/ * elf_next_in_group (int /*<<< orphan*/ *) ; 

__attribute__((used)) static asection *
match_group_member (asection *sec, asection *group,
		    struct bfd_link_info *info)
{
  asection *first = elf_next_in_group (group);
  asection *s = first;

  while (s != NULL)
    {
      if (bfd_elf_match_symbols_in_sections (s, sec, info))
	return s;

      s = elf_next_in_group (s);
      if (s == first)
	break;
    }

  return NULL;
}