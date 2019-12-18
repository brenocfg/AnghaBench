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

/* Variables and functions */
 scalar_t__ SPARC_OPCODE_ARCH_V9_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_architecture ; 
 char* strchr (char*,char) ; 
 unsigned int strtoul (char*,char**,int) ; 

int
sparc_regname_to_dw2regnum (char *regname)
{
  char *p, *q;

  if (!regname[0])
    return -1;

  q = "goli";
  p = strchr (q, regname[0]);
  if (p)
    {
      if (regname[1] < '0' || regname[1] > '8' || regname[2])
	return -1;
      return (p - q) * 8 + regname[1] - '0';
    }
  if (regname[0] == 's' && regname[1] == 'p' && !regname[2])
    return 14;
  if (regname[0] == 'f' && regname[1] == 'p' && !regname[2])
    return 30;
  if (regname[0] == 'f' || regname[0] == 'r')
    {
      unsigned int regnum;

      regnum = strtoul (regname + 1, &q, 10);
      if (p == q || *q)
        return -1;
      if (regnum >= ((regname[0] == 'f'
		      && SPARC_OPCODE_ARCH_V9_P (max_architecture))
		     ? 64 : 32))
	return -1;
      if (regname[0] == 'f')
	{
          regnum += 32;
          if (regnum >= 64 && (regnum & 1))
	    return -1;
        }
      return regnum;
    }
  return -1;
}