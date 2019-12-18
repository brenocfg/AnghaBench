#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int value; } ;
struct TYPE_10__ {TYPE_1__ def; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_3__ root; } ;
struct elf32_arm_link_hash_table {int thumb_glue_size; int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {int dummy; } ;
typedef  int bfd_vma ;
typedef  int bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int output_offset; int vma; TYPE_4__* output_section; int /*<<< orphan*/ * contents; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_5__ asection ;
struct TYPE_12__ {int vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  INTERWORK_FLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THUMB2ARM_GLUE_SECTION_NAME ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 unsigned long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 struct elf_link_hash_entry* find_thumb_glue (struct bfd_link_info*,char const*,char**) ; 
 scalar_t__ insert_thumb_branch (unsigned long,long) ; 
 int /*<<< orphan*/  put_arm_insn (struct elf32_arm_link_hash_table*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_thumb_insn (struct elf32_arm_link_hash_table*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ t2a1_bx_pc_insn ; 
 scalar_t__ t2a2_noop_insn ; 
 scalar_t__ t2a3_b_insn ; 

__attribute__((used)) static int
elf32_thumb_to_arm_stub (struct bfd_link_info * info,
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
  asection * s = 0;
  bfd_vma my_offset;
  unsigned long int tmp;
  long int ret_offset;
  struct elf_link_hash_entry * myh;
  struct elf32_arm_link_hash_table * globals;

  myh = find_thumb_glue (info, name, error_message);
  if (myh == NULL)
    return FALSE;

  globals = elf32_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  my_offset = myh->root.u.def.value;

  s = bfd_get_section_by_name (globals->bfd_of_glue_owner,
			       THUMB2ARM_GLUE_SECTION_NAME);

  BFD_ASSERT (s != NULL);
  BFD_ASSERT (s->contents != NULL);
  BFD_ASSERT (s->output_section != NULL);

  if ((my_offset & 0x01) == 0x01)
    {
      if (sym_sec != NULL
	  && sym_sec->owner != NULL
	  && !INTERWORK_FLAG (sym_sec->owner))
	{
	  (*_bfd_error_handler)
	    (_("%B(%s): warning: interworking not enabled.\n"
	       "  first occurrence: %B: thumb call to arm"),
	     sym_sec->owner, input_bfd, name);

	  return FALSE;
	}

      --my_offset;
      myh->root.u.def.value = my_offset;

      put_thumb_insn (globals, output_bfd, (bfd_vma) t2a1_bx_pc_insn,
		      s->contents + my_offset);

      put_thumb_insn (globals, output_bfd, (bfd_vma) t2a2_noop_insn,
		      s->contents + my_offset + 2);

      ret_offset =
	/* Address of destination of the stub.  */
	((bfd_signed_vma) val)
	- ((bfd_signed_vma)
	   /* Offset from the start of the current section
	      to the start of the stubs.  */
	   (s->output_offset
	    /* Offset of the start of this stub from the start of the stubs.  */
	    + my_offset
	    /* Address of the start of the current section.  */
	    + s->output_section->vma)
	   /* The branch instruction is 4 bytes into the stub.  */
	   + 4
	   /* ARM branches work from the pc of the instruction + 8.  */
	   + 8);

      put_arm_insn (globals, output_bfd,
		    (bfd_vma) t2a3_b_insn | ((ret_offset >> 2) & 0x00FFFFFF),
		    s->contents + my_offset + 4);
    }

  BFD_ASSERT (my_offset <= globals->thumb_glue_size);

  /* Now go back and fix up the original BL insn to point to here.  */
  ret_offset =
    /* Address of where the stub is located.  */
    (s->output_section->vma + s->output_offset + my_offset)
     /* Address of where the BL is located.  */
    - (input_section->output_section->vma + input_section->output_offset
       + offset)
    /* Addend in the relocation.  */
    - addend
    /* Biassing for PC-relative addressing.  */
    - 8;

  tmp = bfd_get_32 (input_bfd, hit_data
		    - input_section->vma);

  bfd_put_32 (output_bfd,
	      (bfd_vma) insert_thumb_branch (tmp, ret_offset),
	      hit_data - input_section->vma);

  return TRUE;
}