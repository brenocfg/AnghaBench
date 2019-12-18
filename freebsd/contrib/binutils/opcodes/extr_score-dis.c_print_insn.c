#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct disassemble_info {int bytes_per_chunk; int (* read_memory_func ) (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ;int /*<<< orphan*/  (* memory_error_func ) (int,int,struct disassemble_info*) ;int /*<<< orphan*/  display_endian; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  BFD_ENDIAN_LITTLE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  print_insn_parallel_sym (struct disassemble_info*) ; 
 int print_insn_score16 (int,struct disassemble_info*,long) ; 
 int print_insn_score32 (int,struct disassemble_info*,long) ; 
 int stub1 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub2 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub3 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub4 (int,int,struct disassemble_info*) ; 

__attribute__((used)) static int
print_insn (bfd_vma pc, struct disassemble_info *info, bfd_boolean little)
{
  unsigned char b[4];
  long given;
  long ridparity;
  int status;
  bfd_boolean insn_pce_p = FALSE;
  bfd_boolean insn_16_p = FALSE;

  info->display_endian = little ? BFD_ENDIAN_LITTLE : BFD_ENDIAN_BIG;

  if (pc & 0x2)
    {
      info->bytes_per_chunk = 2;
      status = info->read_memory_func (pc, (bfd_byte *) b, 2, info);
      b[3] = b[2] = 0;
      insn_16_p = TRUE;
    }
  else
    {
      info->bytes_per_chunk = 4;
      status = info->read_memory_func (pc, (bfd_byte *) & b[0], 4, info);
      if (status != 0)
	{
          info->bytes_per_chunk = 2;
          status = info->read_memory_func (pc, (bfd_byte *) b, 2, info);
          b[3] = b[2] = 0;
          insn_16_p = TRUE;
	}
    }

  if (status != 0)
    {
      info->memory_error_func (status, pc, info);
      return -1;
    }

  if (little)
    {
      given = (b[0]) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    }
  else
    {
      given = (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]);
    }

  if ((given & 0x80008000) == 0x80008000)
    {
      insn_pce_p = FALSE;
      insn_16_p = FALSE;
    }
  else if ((given & 0x8000) == 0x8000)
    {
      insn_pce_p = TRUE;
    }
  else
    {
      insn_16_p = TRUE;
    }

  /* 16 bit instruction.  */
  if (insn_16_p)
    {
      if (little)
	{
          given = b[0] | (b[1] << 8);
	}
      else
	{
          given = (b[0] << 8) | b[1];
	}

      status = print_insn_score16 (pc, info, given);
    }
  /* pce instruction.  */
  else if (insn_pce_p)
    {
      long other;

      other = given & 0xFFFF;
      given = (given & 0xFFFF0000) >> 16;

      status = print_insn_score16 (pc, info, given);
      print_insn_parallel_sym (info);
      status += print_insn_score16 (pc, info, other);
      /* disassemble_bytes() will output 4 byte per chunk for pce instructio.  */
      info->bytes_per_chunk = 4;
    }
  /* 32 bit instruction.  */
  else
    {
      /* Get rid of parity.  */
      ridparity = (given & 0x7FFF);
      ridparity |= (given & 0x7FFF0000) >> 1;
      given = ridparity;
      status = print_insn_score32 (pc, info, given);
    }

  return status;
}