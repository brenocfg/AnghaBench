#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ string; } ;
struct TYPE_7__ {TYPE_5__* section; scalar_t__ value; } ;
struct TYPE_8__ {TYPE_2__ def; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_4__ root; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {TYPE_1__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_5__ asection ;
struct TYPE_6__ {scalar_t__ vma; } ;

/* Variables and functions */
 int SECTION_NAME_MAP_LENGTH ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int /*<<< orphan*/  minfo (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_space () ; 

__attribute__((used)) static bfd_boolean
print_one_symbol (struct bfd_link_hash_entry *hash_entry, void *ptr)
{
  asection *sec = ptr;

  if ((hash_entry->type == bfd_link_hash_defined
       || hash_entry->type == bfd_link_hash_defweak)
      && sec == hash_entry->u.def.section)
    {
      int i;

      for (i = 0; i < SECTION_NAME_MAP_LENGTH; i++)
	print_space ();
      minfo ("0x%V   ",
	     (hash_entry->u.def.value
	      + hash_entry->u.def.section->output_offset
	      + hash_entry->u.def.section->output_section->vma));

      minfo ("             %T\n", hash_entry->root.string);
    }

  return TRUE;
}