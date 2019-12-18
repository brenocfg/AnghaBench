#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* string; } ;
struct TYPE_8__ {TYPE_1__ root; } ;
struct elf_link_hash_entry {int forced_local; int /*<<< orphan*/  type; TYPE_2__ root; } ;
struct TYPE_10__ {scalar_t__ is_relocatable_executable; } ;
struct elf32_arm_link_hash_table {scalar_t__ arm_glue_size; scalar_t__ use_blx; scalar_t__ pic_veneer; TYPE_4__ root; int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {scalar_t__ shared; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ asection ;

/* Variables and functions */
 char* ARM2THUMB_GLUE_ENTRY_NAME ; 
 int /*<<< orphan*/  ARM2THUMB_GLUE_SECTION_NAME ; 
 scalar_t__ ARM2THUMB_PIC_GLUE_SIZE ; 
 scalar_t__ ARM2THUMB_STATIC_GLUE_SIZE ; 
 scalar_t__ ARM2THUMB_V5_STATIC_GLUE_SIZE ; 
 int /*<<< orphan*/  BFD_ASSERT (char*) ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 int /*<<< orphan*/  STT_FUNC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 TYPE_3__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bfd_malloc (scalar_t__) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct elf_link_hash_entry *
record_arm_to_thumb_glue (struct bfd_link_info * link_info,
			  struct elf_link_hash_entry * h)
{
  const char * name = h->root.root.string;
  asection * s;
  char * tmp_name;
  struct elf_link_hash_entry * myh;
  struct bfd_link_hash_entry * bh;
  struct elf32_arm_link_hash_table * globals;
  bfd_vma val;
  bfd_size_type size;

  globals = elf32_arm_hash_table (link_info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  s = bfd_get_section_by_name
    (globals->bfd_of_glue_owner, ARM2THUMB_GLUE_SECTION_NAME);

  BFD_ASSERT (s != NULL);

  tmp_name = bfd_malloc ((bfd_size_type) strlen (name) + strlen (ARM2THUMB_GLUE_ENTRY_NAME) + 1);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, ARM2THUMB_GLUE_ENTRY_NAME, name);

  myh = elf_link_hash_lookup
    (&(globals)->root, tmp_name, FALSE, FALSE, TRUE);

  if (myh != NULL)
    {
      /* We've already seen this guy.  */
      free (tmp_name);
      return myh;
    }

  /* The only trick here is using hash_table->arm_glue_size as the value.
     Even though the section isn't allocated yet, this is where we will be
     putting it.  */
  bh = NULL;
  val = globals->arm_glue_size + 1;
  _bfd_generic_link_add_one_symbol (link_info, globals->bfd_of_glue_owner,
				    tmp_name, BSF_GLOBAL, s, val,
				    NULL, TRUE, FALSE, &bh);

  myh = (struct elf_link_hash_entry *) bh;
  myh->type = ELF_ST_INFO (STB_LOCAL, STT_FUNC);
  myh->forced_local = 1;

  free (tmp_name);

  if (link_info->shared || globals->root.is_relocatable_executable
      || globals->pic_veneer)
    size = ARM2THUMB_PIC_GLUE_SIZE;
  else if (globals->use_blx)
    size = ARM2THUMB_V5_STATIC_GLUE_SIZE;
  else
    size = ARM2THUMB_STATIC_GLUE_SIZE;

  s->size += size;
  globals->arm_glue_size += size;

  return myh;
}