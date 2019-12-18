#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
struct TYPE_7__ {int flags; scalar_t__ size; struct TYPE_7__* kept_section; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_GROUP ; 
 TYPE_1__* match_group_member (TYPE_1__*,TYPE_1__*,struct bfd_link_info*) ; 

asection *
_bfd_elf_check_kept_section (asection *sec, struct bfd_link_info *info)
{
  asection *kept;

  kept = sec->kept_section;
  if (kept != NULL)
    {
      if ((kept->flags & SEC_GROUP) != 0)
	kept = match_group_member (sec, kept, info);
      if (kept != NULL && sec->size != kept->size)
	kept = NULL;
      sec->kept_section = kept;
    }
  return kept;
}