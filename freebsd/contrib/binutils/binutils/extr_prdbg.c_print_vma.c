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
typedef  int /*<<< orphan*/  vma ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  sprintf_vma (char*,scalar_t__) ; 

__attribute__((used)) static void
print_vma (bfd_vma vma, char *buf, bfd_boolean unsignedp, bfd_boolean hexp)
{
  if (sizeof (vma) <= sizeof (unsigned long))
    {
      if (hexp)
	sprintf (buf, "0x%lx", (unsigned long) vma);
      else if (unsignedp)
	sprintf (buf, "%lu", (unsigned long) vma);
      else
	sprintf (buf, "%ld", (long) vma);
    }
  else
    {
      buf[0] = '0';
      buf[1] = 'x';
      sprintf_vma (buf + 2, vma);
    }
}