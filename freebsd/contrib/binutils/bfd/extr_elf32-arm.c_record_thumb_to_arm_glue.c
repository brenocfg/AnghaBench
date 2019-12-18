#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* string; } ;
struct TYPE_7__ {TYPE_1__ root; } ;
struct elf_link_hash_entry {int forced_local; int /*<<< orphan*/  type; TYPE_2__ root; } ;
struct elf32_arm_link_hash_table {scalar_t__ thumb_glue_size; int /*<<< orphan*/ * bfd_of_glue_owner; int /*<<< orphan*/  root; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (char*) ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  BSF_LOCAL ; 
 char* CHANGE_TO_ARM ; 
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 int /*<<< orphan*/  STT_ARM_TFUNC ; 
 char* THUMB2ARM_GLUE_ENTRY_NAME ; 
 int /*<<< orphan*/  THUMB2ARM_GLUE_SECTION_NAME ; 
 scalar_t__ THUMB2ARM_GLUE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 TYPE_3__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bfd_malloc (scalar_t__) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
record_thumb_to_arm_glue (struct bfd_link_info *link_info,
			  struct elf_link_hash_entry *h)
{
  const char *name = h->root.root.string;
  asection *s;
  char *tmp_name;
  struct elf_link_hash_entry *myh;
  struct bfd_link_hash_entry *bh;
  struct elf32_arm_link_hash_table *hash_table;
  bfd_vma val;

  hash_table = elf32_arm_hash_table (link_info);

  BFD_ASSERT (hash_table != NULL);
  BFD_ASSERT (hash_table->bfd_of_glue_owner != NULL);

  s = bfd_get_section_by_name
    (hash_table->bfd_of_glue_owner, THUMB2ARM_GLUE_SECTION_NAME);

  BFD_ASSERT (s != NULL);

  tmp_name = bfd_malloc ((bfd_size_type) strlen (name)
			 + strlen (THUMB2ARM_GLUE_ENTRY_NAME) + 1);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, THUMB2ARM_GLUE_ENTRY_NAME, name);

  myh = elf_link_hash_lookup
    (&(hash_table)->root, tmp_name, FALSE, FALSE, TRUE);

  if (myh != NULL)
    {
      /* We've already seen this guy.  */
      free (tmp_name);
      return;
    }

  bh = NULL;
  val = hash_table->thumb_glue_size + 1;
  _bfd_generic_link_add_one_symbol (link_info, hash_table->bfd_of_glue_owner,
				    tmp_name, BSF_GLOBAL, s, val,
				    NULL, TRUE, FALSE, &bh);

  /* If we mark it 'Thumb', the disassembler will do a better job.  */
  myh = (struct elf_link_hash_entry *) bh;
  myh->type = ELF_ST_INFO (STB_LOCAL, STT_ARM_TFUNC);
  myh->forced_local = 1;

  free (tmp_name);

#define CHANGE_TO_ARM "__%s_change_to_arm"
#define BACK_FROM_ARM "__%s_back_from_arm"

  /* Allocate another symbol to mark where we switch to Arm mode.  */
  tmp_name = bfd_malloc ((bfd_size_type) strlen (name)
			 + strlen (CHANGE_TO_ARM) + 1);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, CHANGE_TO_ARM, name);

  bh = NULL;
  val = hash_table->thumb_glue_size + 4,
  _bfd_generic_link_add_one_symbol (link_info, hash_table->bfd_of_glue_owner,
				    tmp_name, BSF_LOCAL, s, val,
				    NULL, TRUE, FALSE, &bh);

  free (tmp_name);

  s->size += THUMB2ARM_GLUE_SIZE;
  hash_table->thumb_glue_size += THUMB2ARM_GLUE_SIZE;

  return;
}