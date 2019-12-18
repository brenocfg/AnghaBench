#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* read_memory_func ) (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ;scalar_t__ endian; int /*<<< orphan*/  (* memory_error_func ) (int,int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int CGEN_MAX_INSN_SIZE ; 
 int mep_print_vliw_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mep_examine_vliw64_insns (CGEN_CPU_DESC cd, bfd_vma pc, disassemble_info *info)
{
  int status;
  int buflength;
  int corebuflength;
  int cop1buflength;
  int cop2buflength;
  bfd_byte buf[CGEN_MAX_INSN_SIZE];
  char indicator16[1];
  char indicator64[4];

  /* At this time we're not supporting internally parallel
     coprocessors, so cop2buflength will always be 0.  */
  cop2buflength = 0;

  /* Read in 64 bits.  */
  buflength = 8; /* VLIW insn spans 8 bytes.  */
  status = (*info->read_memory_func) (pc, buf, buflength, info);

  if (status != 0)
    {
      (*info->memory_error_func) (status, pc, info);
      return -1;
    }

  /* We have all 64 bits in the buffer now.  We have to figure out
     what combination of instruction sizes are present.  The two
     high order bits will indicate whether or not we have a 16 bit
     core insn or not.  If not, then we have to look at the 7,8th
     bytes to tell whether we have 64 bit copro insn or a 32 bit
     core insn with a 32 bit copro insn.  Endianness will make a
     difference here.  */

  /* Put the big endian representation of the bytes to be examined
     in the temporary buffers for examination.  */

  /* indicator16[0] = buf[0];  */
  if (info->endian == BFD_ENDIAN_BIG)
    {
      indicator16[0] = buf[0];
      indicator64[0] = buf[0];
      indicator64[1] = buf[1];
      indicator64[2] = buf[2];
      indicator64[3] = buf[3];
    }
  else
    {
      indicator16[0] = buf[1];
      indicator64[0] = buf[1];
      indicator64[1] = buf[0];
      indicator64[2] = buf[3];
      indicator64[3] = buf[2];
    }

  /* If the two high order bits are 00, 01 or 10, we have a 16 bit
     core insn and a 48 bit copro insn.  */

  if ((indicator16[0] & 0x80) && (indicator16[0] & 0x40))
    {
      if ((indicator64[0] & 0xf0) == 0xf0 && (indicator64[1] & 0x07) == 0x07
	  && ((indicator64[2] & 0xfe) != 0xf0 || (indicator64[3] & 0xf4) != 0))
	{
          /* We have a 64 bit copro insn.  */
          corebuflength = 0;
	  /* All 8 bytes are one copro insn.  */
          cop1buflength = 8;
	}
      else
	{
          /* We have a 32 bit core insn and a 32 bit copro insn.  */
          corebuflength = 4;
          cop1buflength = 4;
	}
    }
  else
    {
      /* We have a 16 bit core insn and a 48 bit copro insn.  */
      corebuflength = 2;
      cop1buflength = 6;
    }

  /* Now we have the distrubution set.  Print them out. */
  status = mep_print_vliw_insns (cd, pc, info, buf, corebuflength,
				 cop1buflength, cop2buflength);

  return status;
}