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
struct coff_link_hash_entry {TYPE_2__ root; } ;
struct coff_arm_link_hash_table {scalar_t__ arm_glue_size; int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 char* ARM2THUMB_GLUE_ENTRY_NAME ; 
 int /*<<< orphan*/  ARM2THUMB_GLUE_SECTION_NAME ; 
 scalar_t__ ARM2THUMB_GLUE_SIZE ; 
 int /*<<< orphan*/  BFD_ASSERT (char*) ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  FALSE ; 
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
record_arm_to_thumb_glue (struct bfd_link_info *        info,
			  struct coff_link_hash_entry * h)
{
  const char *                      name = h->root.root.string;
  register asection *               s;
  char *                            tmp_name;
  struct coff_link_hash_entry *     myh;
  struct bfd_link_hash_entry *      bh;
  struct coff_arm_link_hash_table * globals;
  bfd_vma val;
  bfd_size_type amt;

  globals = coff_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  s = bfd_get_section_by_name
    (globals->bfd_of_glue_owner, ARM2THUMB_GLUE_SECTION_NAME);

  BFD_ASSERT (s != NULL);

  amt = strlen (name) + strlen (ARM2THUMB_GLUE_ENTRY_NAME) + 1;
  tmp_name = bfd_malloc (amt);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, ARM2THUMB_GLUE_ENTRY_NAME, name);

  myh = coff_link_hash_lookup
    (coff_hash_table (info), tmp_name, FALSE, FALSE, TRUE);

  if (myh != NULL)
    {
      free (tmp_name);
      /* We've already seen this guy.  */
      return;
    }

  /* The only trick here is using globals->arm_glue_size as the value. Even
     though the section isn't allocated yet, this is where we will be putting
     it.  */
  bh = NULL;
  val = globals->arm_glue_size + 1;
  bfd_coff_link_add_one_symbol (info, globals->bfd_of_glue_owner, tmp_name,
				BSF_GLOBAL, s, val, NULL, TRUE, FALSE, &bh);

  free (tmp_name);

  globals->arm_glue_size += ARM2THUMB_GLUE_SIZE;

  return;
}