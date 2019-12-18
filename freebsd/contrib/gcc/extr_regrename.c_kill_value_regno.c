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
struct value_data {unsigned int max_value_regs; TYPE_1__* e; } ;
struct TYPE_2__ {size_t mode; } ;

/* Variables and functions */
 size_t VOIDmode ; 
 unsigned int** hard_regno_nregs ; 
 int /*<<< orphan*/  kill_value_one_regno (unsigned int,struct value_data*) ; 

__attribute__((used)) static void
kill_value_regno (unsigned int regno, unsigned int nregs,
		  struct value_data *vd)
{
  unsigned int j;

  /* Kill the value we're told to kill.  */
  for (j = 0; j < nregs; ++j)
    kill_value_one_regno (regno + j, vd);

  /* Kill everything that overlapped what we're told to kill.  */
  if (regno < vd->max_value_regs)
    j = 0;
  else
    j = regno - vd->max_value_regs;
  for (; j < regno; ++j)
    {
      unsigned int i, n;
      if (vd->e[j].mode == VOIDmode)
	continue;
      n = hard_regno_nregs[j][vd->e[j].mode];
      if (j + n > regno)
	for (i = 0; i < n; ++i)
	  kill_value_one_regno (j + i, vd);
    }
}