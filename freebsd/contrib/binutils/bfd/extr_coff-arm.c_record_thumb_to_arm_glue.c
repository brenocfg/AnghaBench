#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* string; } ;
struct TYPE_4__ {TYPE_1__ root; } ;
struct coff_link_hash_entry {int /*<<< orphan*/  class; TYPE_2__ root; } ;
struct coff_arm_link_hash_table {scalar_t__ thumb_glue_size; int /*<<< orphan*/ * bfd_of_glue_owner; scalar_t__ support_old_code; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 char* BACK_FROM_ARM ; 
 int /*<<< orphan*/  BFD_ASSERT (char*) ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  BSF_LOCAL ; 
 char* CHANGE_TO_ARM ; 
 int /*<<< orphan*/  C_THUMBEXTFUNC ; 
 int /*<<< orphan*/  FALSE ; 
 char* THUMB2ARM_GLUE_ENTRY_NAME ; 
 int /*<<< orphan*/  THUMB2ARM_GLUE_SECTION_NAME ; 
 scalar_t__ THUMB2ARM_GLUE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_coff_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bfd_malloc (scalar_t__) ; 
 struct coff_arm_link_hash_table* coff_arm_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  coff_hash_table (struct bfd_link_info*) ; 
 struct coff_link_hash_entry* coff_link_hash_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
record_thumb_to_arm_glue (struct bfd_link_info *        info,
			  struct coff_link_hash_entry * h)
{
  const char *                       name = h->root.root.string;
  asection *                         s;
  char *                             tmp_name;
  struct coff_link_hash_entry *      myh;
  struct bfd_link_hash_entry *       bh;
  struct coff_arm_link_hash_table *  globals;
  bfd_vma val;
  bfd_size_type amt;

  globals = coff_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  s = bfd_get_section_by_name
    (globals->bfd_of_glue_owner, THUMB2ARM_GLUE_SECTION_NAME);

  BFD_ASSERT (s != NULL);

  amt = strlen (name) + strlen (THUMB2ARM_GLUE_ENTRY_NAME) + 1;
  tmp_name = bfd_malloc (amt);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, THUMB2ARM_GLUE_ENTRY_NAME, name);

  myh = coff_link_hash_lookup
    (coff_hash_table (info), tmp_name, FALSE, FALSE, TRUE);

  if (myh != NULL)
    {
      free (tmp_name);
      /* We've already seen this guy.  */
      return;
    }

  bh = NULL;
  val = globals->thumb_glue_size + 1;
  bfd_coff_link_add_one_symbol (info, globals->bfd_of_glue_owner, tmp_name,
				BSF_GLOBAL, s, val, NULL, TRUE, FALSE, &bh);

  /* If we mark it 'thumb', the disassembler will do a better job.  */
  myh = (struct coff_link_hash_entry *) bh;
  myh->class = C_THUMBEXTFUNC;

  free (tmp_name);

  /* Allocate another symbol to mark where we switch to arm mode.  */

#define CHANGE_TO_ARM "__%s_change_to_arm"
#define BACK_FROM_ARM "__%s_back_from_arm"

  amt = strlen (name) + strlen (CHANGE_TO_ARM) + 1;
  tmp_name = bfd_malloc (amt);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, globals->support_old_code ? BACK_FROM_ARM : CHANGE_TO_ARM, name);

  bh = NULL;
  val = globals->thumb_glue_size + (globals->support_old_code ? 8 : 4);
  bfd_coff_link_add_one_symbol (info, globals->bfd_of_glue_owner, tmp_name,
				BSF_LOCAL, s, val, NULL, TRUE, FALSE, &bh);

  free (tmp_name);

  globals->thumb_glue_size += THUMB2ARM_GLUE_SIZE;

  return;
}