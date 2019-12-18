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
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_signed_vma ;

/* Variables and functions */
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static int
print_dec_vma (bfd_vma vma, int is_signed)
{
  char buf[40];
  char *bufp = buf;
  int nc = 0;

  if (is_signed && (bfd_signed_vma) vma < 0)
    {
      vma = -vma;
      putchar ('-');
      nc = 1;
    }

  do
    {
      *bufp++ = '0' + vma % 10;
      vma /= 10;
    }
  while (vma != 0);
  nc += bufp - buf;

  while (bufp > buf)
    putchar (*--bufp);
  return nc;
}