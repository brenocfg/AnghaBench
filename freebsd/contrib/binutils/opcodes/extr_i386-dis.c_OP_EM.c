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
 int /*<<< orphan*/  MODRM_CHECK ; 
 int /*<<< orphan*/  OP_E (int,int) ; 
 int PREFIX_DATA ; 
 int REX_B ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int /*<<< orphan*/  codep ; 
 size_t intel_syntax ; 
 TYPE_1__ modrm ; 
 int /*<<< orphan*/  oappend (int /*<<< orphan*/ *) ; 
 int prefixes ; 
 int q_mode ; 
 int rex ; 
 int /*<<< orphan*/ * scratchbuf ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 
 int used_prefixes ; 
 int v_mode ; 
 int x_mode ; 

__attribute__((used)) static void
OP_EM (int bytemode, int sizeflag)
{
  if (modrm.mod != 3)
    {
      if (intel_syntax && bytemode == v_mode)
	{
	  bytemode = (prefixes & PREFIX_DATA) ? x_mode : q_mode;
	  used_prefixes |= (prefixes & PREFIX_DATA);
 	}
      OP_E (bytemode, sizeflag);
      return;
    }

  /* Skip mod/rm byte.  */
  MODRM_CHECK;
  codep++;
  used_prefixes |= (prefixes & PREFIX_DATA);
  if (prefixes & PREFIX_DATA)
    {
      int add = 0;

      USED_REX (REX_B);
      if (rex & REX_B)
	add = 8;
      sprintf (scratchbuf, "%%xmm%d", modrm.rm + add);
    }
  else
    sprintf (scratchbuf, "%%mm%d", modrm.rm);
  oappend (&scratchbuf[intel_syntax]);
}