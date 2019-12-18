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
typedef  int /*<<< orphan*/  B_TYPE ;

/* Variables and functions */
 scalar_t__ B_TST (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
print_bit_vector (B_TYPE *bits, int nbits)
{
  int bitno;

  for (bitno = 0; bitno < nbits; bitno++)
    {
      if ((bitno % 8) == 0)
	{
	  puts_filtered (" ");
	}
      if (B_TST (bits, bitno))
	{
	  printf_filtered ("1");
	}
      else
	{
	  printf_filtered ("0");
	}
    }
}