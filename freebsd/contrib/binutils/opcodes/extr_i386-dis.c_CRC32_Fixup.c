#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mod; int rm; } ;

/* Variables and functions */
 int DFLAG ; 
 int /*<<< orphan*/  INTERNAL_DISASSEMBLER_ERROR ; 
 int /*<<< orphan*/  MODRM_CHECK ; 
 int /*<<< orphan*/  OP_E (int,int) ; 
 int PREFIX_DATA ; 
 int REX_B ; 
 int REX_W ; 
 int /*<<< orphan*/  USED_REX (int) ; 
#define  b_mode 129 
 int /*<<< orphan*/  codep ; 
 int /*<<< orphan*/  intel_syntax ; 
 TYPE_1__ modrm ; 
 int /*<<< orphan*/ * names16 ; 
 int /*<<< orphan*/ * names32 ; 
 int /*<<< orphan*/ * names64 ; 
 int /*<<< orphan*/ * names8 ; 
 int /*<<< orphan*/ * names8rex ; 
 int /*<<< orphan*/  oappend (int /*<<< orphan*/ ) ; 
 char* obuf ; 
 int prefixes ; 
 int rex ; 
 int strlen (char*) ; 
 int used_prefixes ; 
#define  v_mode 128 

__attribute__((used)) static void
CRC32_Fixup (int bytemode, int sizeflag)
{
  /* Add proper suffix to "crc32".  */
  char *p = obuf + strlen (obuf);

  switch (bytemode)
    {
    case b_mode:
      if (intel_syntax)
	break;

      *p++ = 'b';
      break;
    case v_mode:
      if (intel_syntax)
	break;

      USED_REX (REX_W);
      if (rex & REX_W)
	*p++ = 'q';
      else if (sizeflag & DFLAG)
	*p++ = 'l';
      else
	*p++ = 'w';
      used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    default:
      oappend (INTERNAL_DISASSEMBLER_ERROR);
      break;
    }
  *p = '\0';

  if (modrm.mod == 3)
    {
      int add;

      /* Skip mod/rm byte.  */
      MODRM_CHECK;
      codep++;

      USED_REX (REX_B);
      add = (rex & REX_B) ? 8 : 0;
      if (bytemode == b_mode)
	{
	  USED_REX (0);
	  if (rex)
	    oappend (names8rex[modrm.rm + add]);
	  else
	    oappend (names8[modrm.rm + add]);
	}
      else
	{
	  USED_REX (REX_W);
	  if (rex & REX_W)
	    oappend (names64[modrm.rm + add]);
	  else if ((prefixes & PREFIX_DATA))
	    oappend (names16[modrm.rm + add]);
	  else
	    oappend (names32[modrm.rm + add]);
	}
    }
  else
    OP_E (bytemode, sizeflag);
}