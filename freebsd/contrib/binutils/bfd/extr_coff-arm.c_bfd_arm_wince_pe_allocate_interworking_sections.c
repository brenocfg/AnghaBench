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
struct coff_arm_link_hash_table {scalar_t__ arm_glue_size; scalar_t__ thumb_glue_size; int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  ARM2THUMB_GLUE_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THUMB2ARM_GLUE_SECTION_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct coff_arm_link_hash_table* coff_arm_hash_table (struct bfd_link_info*) ; 

bfd_boolean
bfd_arm_allocate_interworking_sections (struct bfd_link_info * info)
{
  asection *                        s;
  bfd_byte *                        foo;
  struct coff_arm_link_hash_table * globals;

  globals = coff_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);

  if (globals->arm_glue_size != 0)
    {
      BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

      s = bfd_get_section_by_name
	(globals->bfd_of_glue_owner, ARM2THUMB_GLUE_SECTION_NAME);

      BFD_ASSERT (s != NULL);

      foo = bfd_alloc (globals->bfd_of_glue_owner, globals->arm_glue_size);

      s->size = globals->arm_glue_size;
      s->contents = foo;
    }

  if (globals->thumb_glue_size != 0)
    {
      BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

      s = bfd_get_section_by_name
	(globals->bfd_of_glue_owner, THUMB2ARM_GLUE_SECTION_NAME);

      BFD_ASSERT (s != NULL);

      foo = bfd_alloc (globals->bfd_of_glue_owner, globals->thumb_glue_size);

      s->size = globals->thumb_glue_size;
      s->contents = foo;
    }

  return TRUE;
}