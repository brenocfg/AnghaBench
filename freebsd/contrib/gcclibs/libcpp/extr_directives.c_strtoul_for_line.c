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
typedef  scalar_t__ uchar ;

/* Variables and functions */
 int /*<<< orphan*/  ISDIGIT (scalar_t__) ; 

__attribute__((used)) static int
strtoul_for_line (const uchar *str, unsigned int len, long unsigned int *nump)
{
  unsigned long reg = 0;
  uchar c;
  while (len--)
    {
      c = *str++;
      if (!ISDIGIT (c))
	return 1;
      reg *= 10;
      reg += c - '0';
    }
  *nump = reg;
  return 0;
}