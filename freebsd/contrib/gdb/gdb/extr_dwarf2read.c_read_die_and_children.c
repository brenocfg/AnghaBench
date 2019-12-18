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
struct die_info {struct die_info* parent; int /*<<< orphan*/ * sibling; int /*<<< orphan*/ * child; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/ * read_die_and_siblings (char*,int /*<<< orphan*/ *,struct dwarf2_cu*,char**,struct die_info*) ; 
 char* read_full_die (struct die_info**,int /*<<< orphan*/ *,char*,struct dwarf2_cu*,int*) ; 
 int /*<<< orphan*/  store_in_ref_table (int /*<<< orphan*/ ,struct die_info*) ; 

__attribute__((used)) static struct die_info *
read_die_and_children (char *info_ptr, bfd *abfd,
		       struct dwarf2_cu *cu,
		       char **new_info_ptr,
		       struct die_info *parent)
{
  struct die_info *die;
  char *cur_ptr;
  int has_children;

  cur_ptr = read_full_die (&die, abfd, info_ptr, cu, &has_children);
  store_in_ref_table (die->offset, die);

  if (has_children)
    {
      die->child = read_die_and_siblings (cur_ptr, abfd, cu,
					  new_info_ptr, die);
    }
  else
    {
      die->child = NULL;
      *new_info_ptr = cur_ptr;
    }

  die->sibling = NULL;
  die->parent = parent;
  return die;
}