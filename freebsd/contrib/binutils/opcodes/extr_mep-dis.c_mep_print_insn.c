#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* section; } ;
typedef  TYPE_5__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_18__ {TYPE_2__* elf_obj_data; } ;
struct TYPE_21__ {TYPE_3__ tdata; } ;
typedef  TYPE_6__ bfd ;
struct TYPE_22__ {int /*<<< orphan*/ * isas; } ;
struct TYPE_19__ {int flags; TYPE_6__* owner; } ;
struct TYPE_17__ {TYPE_1__* elf_header; } ;
struct TYPE_16__ {int e_flags; } ;
typedef  TYPE_7__* CGEN_CPU_DESC ;

/* Variables and functions */
 int EF_MEP_INDEX_MASK ; 
 int /*<<< orphan*/  MEP_CORE_ISA ; 
 scalar_t__ MEP_VLIW64 ; 
 int SEC_MEP_VLIW ; 
 int default_print_insn (TYPE_7__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int mep_config_index ; 
 int mep_examine_vliw32_insns (TYPE_7__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int mep_examine_vliw64_insns (TYPE_7__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int
mep_print_insn (CGEN_CPU_DESC cd, bfd_vma pc, disassemble_info *info)
{
  int status;

  /* Extract and adapt to configuration number, if available. */
  if (info->section && info->section->owner)
    {
      bfd *abfd = info->section->owner;
      mep_config_index = abfd->tdata.elf_obj_data->elf_header->e_flags & EF_MEP_INDEX_MASK;
      /* This instantly redefines MEP_CONFIG, MEP_OMASK, .... MEP_VLIW64 */
    }

  /* Picking the right ISA bitmask for the current context is tricky.  */
  if (info->section)
    {
      if (info->section->flags & SEC_MEP_VLIW)
	{
	  /* Are we in 32 or 64 bit vliw mode?  */
	  if (MEP_VLIW64)
	    status = mep_examine_vliw64_insns (cd, pc, info);
	  else
	    status = mep_examine_vliw32_insns (cd, pc, info);
	  /* Both the above branches set their own isa bitmasks.  */
	}
      else
	{
	  cd->isas = & MEP_CORE_ISA;
	  status = default_print_insn (cd, pc, info);
	}
    }
  else /* sid or gdb */
    {
      status = default_print_insn (cd, pc, info);
    }

  return status;
}