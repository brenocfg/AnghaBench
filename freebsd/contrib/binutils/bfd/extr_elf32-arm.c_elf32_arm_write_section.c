#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct elf32_arm_link_hash_table {scalar_t__ byteswap_code; } ;
struct bfd_link_info {int dummy; } ;
struct TYPE_28__ {TYPE_6__* branch; } ;
struct TYPE_24__ {int vfp_insn; TYPE_2__* veneer; } ;
struct TYPE_29__ {TYPE_7__ v; TYPE_3__ b; } ;
struct TYPE_30__ {int vma; int type; TYPE_8__ u; struct TYPE_30__* next; } ;
typedef  TYPE_9__ elf32_vfp11_erratum_list ;
struct TYPE_19__ {int vma; int type; } ;
typedef  TYPE_10__ elf32_arm_section_map ;
typedef  int bfd_vma ;
typedef  unsigned int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_20__ {int output_offset; int size; TYPE_1__* output_section; } ;
typedef  TYPE_11__ asection ;
struct TYPE_21__ {int mapcount; int erratumcount; TYPE_10__* map; scalar_t__ mapsize; TYPE_9__* erratumlist; } ;
typedef  TYPE_12__ _arm_elf_section_data ;
struct TYPE_25__ {unsigned int vfp_insn; } ;
struct TYPE_26__ {TYPE_4__ b; } ;
struct TYPE_27__ {int vma; TYPE_5__ u; } ;
struct TYPE_23__ {int vma; } ;
struct TYPE_22__ {int vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  VFP11_ERRATUM_ARM_VENEER 129 
#define  VFP11_ERRATUM_BRANCH_TO_ARM_VENEER 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_big_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf32_arm_compare_mapping ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  free (TYPE_10__*) ; 
 TYPE_12__* get_arm_elf_section_data (TYPE_11__*) ; 
 int /*<<< orphan*/  qsort (TYPE_10__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unrecord_section_with_arm_elf_section_data (TYPE_11__*) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_write_section (bfd *output_bfd,
			 struct bfd_link_info *link_info, asection *sec,
			 bfd_byte *contents)
{
  int mapcount, errcount;
  _arm_elf_section_data *arm_data;
  struct elf32_arm_link_hash_table *globals = elf32_arm_hash_table (link_info);
  elf32_arm_section_map *map;
  elf32_vfp11_erratum_list *errnode;
  bfd_vma ptr;
  bfd_vma end;
  bfd_vma offset = sec->output_section->vma + sec->output_offset;
  bfd_byte tmp;
  int i;

  /* If this section has not been allocated an _arm_elf_section_data
     structure then we cannot record anything.  */
  arm_data = get_arm_elf_section_data (sec);
  if (arm_data == NULL)
    return FALSE;

  mapcount = arm_data->mapcount;
  map = arm_data->map;
  errcount = arm_data->erratumcount;

  if (errcount != 0)
    {
      unsigned int endianflip = bfd_big_endian (output_bfd) ? 3 : 0;

      for (errnode = arm_data->erratumlist; errnode != 0;
           errnode = errnode->next)
        {
          bfd_vma index = errnode->vma - offset;

          switch (errnode->type)
            {
            case VFP11_ERRATUM_BRANCH_TO_ARM_VENEER:
              {
                bfd_vma branch_to_veneer;
                /* Original condition code of instruction, plus bit mask for
                   ARM B instruction.  */
                unsigned int insn = (errnode->u.b.vfp_insn & 0xf0000000)
                                  | 0x0a000000;

		/* The instruction is before the label.  */
		index -= 4;

		/* Above offset included in -4 below.  */
		branch_to_veneer = errnode->u.b.veneer->vma
                                   - errnode->vma - 4;

		if ((signed) branch_to_veneer < -(1 << 25)
		    || (signed) branch_to_veneer >= (1 << 25))
		  (*_bfd_error_handler) (_("%B: error: VFP11 veneer out of "
					   "range"), output_bfd);

                insn |= (branch_to_veneer >> 2) & 0xffffff;
                contents[endianflip ^ index] = insn & 0xff;
                contents[endianflip ^ (index + 1)] = (insn >> 8) & 0xff;
                contents[endianflip ^ (index + 2)] = (insn >> 16) & 0xff;
                contents[endianflip ^ (index + 3)] = (insn >> 24) & 0xff;
              }
              break;

	    case VFP11_ERRATUM_ARM_VENEER:
              {
                bfd_vma branch_from_veneer;
                unsigned int insn;

                /* Take size of veneer into account.  */
                branch_from_veneer = errnode->u.v.branch->vma
                                     - errnode->vma - 12;

		if ((signed) branch_from_veneer < -(1 << 25)
		    || (signed) branch_from_veneer >= (1 << 25))
		  (*_bfd_error_handler) (_("%B: error: VFP11 veneer out of "
					   "range"), output_bfd);

                /* Original instruction.  */
                insn = errnode->u.v.branch->u.b.vfp_insn;
                contents[endianflip ^ index] = insn & 0xff;
                contents[endianflip ^ (index + 1)] = (insn >> 8) & 0xff;
                contents[endianflip ^ (index + 2)] = (insn >> 16) & 0xff;
                contents[endianflip ^ (index + 3)] = (insn >> 24) & 0xff;

                /* Branch back to insn after original insn.  */
                insn = 0xea000000 | ((branch_from_veneer >> 2) & 0xffffff);
                contents[endianflip ^ (index + 4)] = insn & 0xff;
                contents[endianflip ^ (index + 5)] = (insn >> 8) & 0xff;
                contents[endianflip ^ (index + 6)] = (insn >> 16) & 0xff;
                contents[endianflip ^ (index + 7)] = (insn >> 24) & 0xff;
              }
              break;

            default:
              abort ();
            }
        }
    }

  if (mapcount == 0)
    return FALSE;

  if (globals->byteswap_code)
    {
      qsort (map, mapcount, sizeof (* map), elf32_arm_compare_mapping);

      ptr = map[0].vma;
      for (i = 0; i < mapcount; i++)
        {
          if (i == mapcount - 1)
	    end = sec->size;
          else
            end = map[i + 1].vma;

          switch (map[i].type)
	    {
	    case 'a':
	      /* Byte swap code words.  */
	      while (ptr + 3 < end)
	        {
	          tmp = contents[ptr];
	          contents[ptr] = contents[ptr + 3];
	          contents[ptr + 3] = tmp;
	          tmp = contents[ptr + 1];
	          contents[ptr + 1] = contents[ptr + 2];
	          contents[ptr + 2] = tmp;
	          ptr += 4;
	        }
	      break;

	    case 't':
	      /* Byte swap code halfwords.  */
	      while (ptr + 1 < end)
	        {
	          tmp = contents[ptr];
	          contents[ptr] = contents[ptr + 1];
	          contents[ptr + 1] = tmp;
	          ptr += 2;
	        }
	      break;

	    case 'd':
	      /* Leave data alone.  */
	      break;
	    }
          ptr = end;
        }
    }

  free (map);
  arm_data->mapcount = 0;
  arm_data->mapsize = 0;
  arm_data->map = NULL;
  unrecord_section_with_arm_elf_section_data (sec);

  return FALSE;
}