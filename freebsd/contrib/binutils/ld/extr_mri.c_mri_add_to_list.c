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
struct section_name_struct {char const* name; char const* alias; int /*<<< orphan*/ * subalign; int /*<<< orphan*/ * align; scalar_t__ ok_to_load; int /*<<< orphan*/ * next; int /*<<< orphan*/ * vma; } ;
typedef  int /*<<< orphan*/  etree_type ;

/* Variables and functions */
 struct section_name_struct** lookup (char const*,struct section_name_struct**) ; 

__attribute__((used)) static void
mri_add_to_list (struct section_name_struct **list,
		 const char *name,
		 etree_type *vma,
		 const char *zalias,
		 etree_type *align,
		 etree_type *subalign)
{
  struct section_name_struct **ptr = lookup (name, list);

  (*ptr)->name = name;
  (*ptr)->vma = vma;
  (*ptr)->next = NULL;
  (*ptr)->ok_to_load = 0;
  (*ptr)->alias = zalias;
  (*ptr)->align = align;
  (*ptr)->subalign = subalign;
}