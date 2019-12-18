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

/* Variables and functions */
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static int
print_hex_vma (bfd_vma vma)
{
  char buf[32];
  char *bufp = buf;
  int nc;

  do
    {
      char digit = '0' + (vma & 0x0f);
      if (digit > '9')
	digit += 'a' - '0' - 10;
      *bufp++ = digit;
      vma >>= 4;
    }
  while (vma != 0);
  nc = bufp - buf;

  while (bufp > buf)
    putchar (*--bufp);
  return nc;
}