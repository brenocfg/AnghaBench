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
 int pluspresent ; 

int
mep_unrecognized_line (int ch)
{
  switch (ch)
    {
    case '+':
      pluspresent = 1;
      return 1; /* '+' indicates an instruction to be parallelized. */
    default:
      return 0; /* If it's not a '+', the line can't be parsed. */
    }
}