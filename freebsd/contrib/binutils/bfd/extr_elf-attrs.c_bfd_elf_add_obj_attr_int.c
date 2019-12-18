#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; unsigned int i; } ;
typedef  TYPE_1__ obj_attribute ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 TYPE_1__* elf_new_obj_attr (int /*<<< orphan*/ *,int,int) ; 

void
bfd_elf_add_obj_attr_int (bfd *abfd, int vendor, int tag, unsigned int i)
{
  obj_attribute *attr;

  attr = elf_new_obj_attr (abfd, vendor, tag);
  attr->type = 1;
  attr->i = i;
}