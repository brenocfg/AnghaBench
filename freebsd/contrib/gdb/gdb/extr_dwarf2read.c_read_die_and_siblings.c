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
struct dwarf2_cu {int dummy; } ;
struct die_info {scalar_t__ tag; struct die_info* sibling; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct die_info* read_die_and_children (char*,int /*<<< orphan*/ *,struct dwarf2_cu*,char**,struct die_info*) ; 

__attribute__((used)) static struct die_info *
read_die_and_siblings (char *info_ptr, bfd *abfd,
		       struct dwarf2_cu *cu,
		       char **new_info_ptr,
		       struct die_info *parent)
{
  struct die_info *first_die, *last_sibling;
  char *cur_ptr;

  cur_ptr = info_ptr;
  first_die = last_sibling = NULL;

  while (1)
    {
      struct die_info *die
	= read_die_and_children (cur_ptr, abfd, cu, &cur_ptr, parent);

      if (!first_die)
	{
	  first_die = die;
	}
      else
	{
	  last_sibling->sibling = die;
	}

      if (die->tag == 0)
	{
	  *new_info_ptr = cur_ptr;
	  return first_die;
	}
      else
	{
	  last_sibling = die;
	}
    }
}