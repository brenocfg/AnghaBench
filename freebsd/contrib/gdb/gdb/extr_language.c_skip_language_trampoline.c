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
struct TYPE_2__ {scalar_t__ (* skip_trampoline ) (scalar_t__) ;} ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 TYPE_1__** languages ; 
 int languages_size ; 
 scalar_t__ stub1 (scalar_t__) ; 

CORE_ADDR 
skip_language_trampoline (CORE_ADDR pc)
{
  int i;

  for (i = 0; i < languages_size; i++)
    {
      if (languages[i]->skip_trampoline)
	{
	  CORE_ADDR real_pc = (languages[i]->skip_trampoline) (pc);
	  if (real_pc)
	    return real_pc;
	}
    }

  return 0;
}