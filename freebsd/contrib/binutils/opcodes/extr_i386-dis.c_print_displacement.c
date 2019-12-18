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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;

/* Variables and functions */
 int address_mode ; 
#define  mode_16bit 130 
#define  mode_32bit 129 
#define  mode_64bit 128 
 int /*<<< orphan*/  sprintf_vma (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
print_displacement (char *buf, bfd_vma disp)
{
  bfd_signed_vma val = disp;
  char tmp[30];
  int i, j = 0;

  if (val < 0)
    {
      buf[j++] = '-';
      val = -disp;

      /* Check for possible overflow.  */
      if (val < 0)
	{
	  switch (address_mode)
	    {
	    case mode_64bit:
	      strcpy (buf + j, "0x8000000000000000");
	      break;
	    case mode_32bit:
	      strcpy (buf + j, "0x80000000");
	      break;
	    case mode_16bit:
	      strcpy (buf + j, "0x8000");
	      break;
	    }
	  return;
	}
    }

  buf[j++] = '0';
  buf[j++] = 'x';

  sprintf_vma (tmp, val);
  for (i = 0; tmp[i] == '0'; i++)
    continue;
  if (tmp[i] == '\0')
    i--;
  strcpy (buf + j, tmp + i);
}