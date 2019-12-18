#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,TYPE_1__*,unsigned char*,scalar_t__,int) ; 
 scalar_t__ is_branch (unsigned char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
find_function_stack_adjust (asection *sec, bfd_vma offset)
{
  int unrecog;
  int reg[128];

  memset (reg, 0, sizeof (reg));
  for (unrecog = 0; offset + 4 <= sec->size && unrecog < 32; offset += 4)
    {
      unsigned char buf[4];
      int rt, ra;
      int imm;

      /* Assume no relocs on stack adjusing insns.  */
      if (!bfd_get_section_contents (sec->owner, sec, buf, offset, 4))
	break;

      if (buf[0] == 0x24 /* stqd */)
	continue;

      rt = buf[3] & 0x7f;
      ra = ((buf[2] & 0x3f) << 1) | (buf[3] >> 7);
      /* Partly decoded immediate field.  */
      imm = (buf[1] << 9) | (buf[2] << 1) | (buf[3] >> 7);

      if (buf[0] == 0x1c /* ai */)
	{
	  imm >>= 7;
	  imm = (imm ^ 0x200) - 0x200;
	  reg[rt] = reg[ra] + imm;

	  if (rt == 1 /* sp */)
	    {
	      if (imm > 0)
		break;
	      return reg[rt];
	    }
	}
      else if (buf[0] == 0x18 && (buf[1] & 0xe0) == 0 /* a */)
	{
	  int rb = ((buf[1] & 0x1f) << 2) | ((buf[2] & 0xc0) >> 6);

	  reg[rt] = reg[ra] + reg[rb];
	  if (rt == 1)
	    return reg[rt];
	}
      else if ((buf[0] & 0xfc) == 0x40 /* il, ilh, ilhu, ila */)
	{
	  if (buf[0] >= 0x42 /* ila */)
	    imm |= (buf[0] & 1) << 17;
	  else
	    {
	      imm &= 0xffff;

	      if (buf[0] == 0x40 /* il */)
		{
		  if ((buf[1] & 0x80) == 0)
		    goto unknown_insn;
		  imm = (imm ^ 0x8000) - 0x8000;
		}
	      else if ((buf[1] & 0x80) == 0 /* ilhu */)
		imm <<= 16;
	    }
	  reg[rt] = imm;
	  continue;
	}
      else if (buf[0] == 0x60 && (buf[1] & 0x80) != 0 /* iohl */)
	{
	  reg[rt] |= imm & 0xffff;
	  continue;
	}
      else if (buf[0] == 0x04 /* ori */)
	{
	  imm >>= 7;
	  imm = (imm ^ 0x200) - 0x200;
	  reg[rt] = reg[ra] | imm;
	  continue;
	}
      else if ((buf[0] == 0x33 && imm == 1 /* brsl .+4 */)
	       || (buf[0] == 0x08 && (buf[1] & 0xe0) == 0 /* sf */))
	{
	  /* Used in pic reg load.  Say rt is trashed.  */
	  reg[rt] = 0;
	  continue;
	}
      else if (is_branch (buf))
	/* If we hit a branch then we must be out of the prologue.  */
	break;
    unknown_insn:
      ++unrecog;
    }

  return 0;
}