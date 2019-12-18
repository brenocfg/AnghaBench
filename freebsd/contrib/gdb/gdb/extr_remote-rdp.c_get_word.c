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
 unsigned int get_byte () ; 

__attribute__((used)) static unsigned int
get_word (void)
{
  unsigned int val = 0;
  unsigned int c;
  int n;
  for (n = 0; n < 4; n++)
    {
      c = get_byte ();
      val |= c << (n * 8);
    }
  return val;
}