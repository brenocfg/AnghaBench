#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int value; } ;
struct TYPE_12__ {TYPE_1__ def; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_3__ root; } ;
struct elf32_arm_link_hash_table {int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {int dummy; } ;
typedef  int bfd_vma ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {int output_offset; int vma; TYPE_4__* output_section; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_5__ asection ;
struct TYPE_14__ {int vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM2THUMB_GLUE_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 unsigned long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct elf_link_hash_entry* elf32_arm_create_thumb_stub (struct bfd_link_info*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int,TYPE_5__*,char**) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static int
elf32_arm_to_thumb_stub (struct bfd_link_info * info,
			 const char *           name,
			 bfd *                  input_bfd,
			 bfd *                  output_bfd,
			 asection *             input_section,
			 bfd_byte *             hit_data,
			 asection *             sym_sec,
			 bfd_vma                offset,
			 bfd_signed_vma         addend,
			 bfd_vma                val,
			 char **error_message)
{
  unsigned long int tmp;
  bfd_vma my_offset;
  asection * s;
  long int ret_offset;
  struct elf_link_hash_entry * myh;
  struct elf32_arm_link_hash_table * globals;

  globals = elf32_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  s = bfd_get_section_by_name (globals->bfd_of_glue_owner,
			       ARM2THUMB_GLUE_SECTION_NAME);
  BFD_ASSERT (s != NULL);
  BFD_ASSERT (s->contents != NULL);
  BFD_ASSERT (s->output_section != NULL);

  myh = elf32_arm_create_thumb_stub (info, name, input_bfd, output_bfd,
				     sym_sec, val, s, error_message);
  if (!myh)
    return FALSE;

  my_offset = myh->root.u.def.value;
  tmp = bfd_get_32 (input_bfd, hit_data);
  tmp = tmp & 0xFF000000;

  /* Somehow these are both 4 too far, so subtract 8.  */
  ret_offset = (s->output_offset
		+ my_offset
		+ s->output_section->vma
		- (input_section->output_offset
		   + input_section->output_section->vma
		   + offset + addend)
		- 8);

  tmp = tmp | ((ret_offset >> 2) & 0x00FFFFFF);

  bfd_put_32 (output_bfd, (bfd_vma) tmp, hit_data - input_section->vma);

  return TRUE;
}