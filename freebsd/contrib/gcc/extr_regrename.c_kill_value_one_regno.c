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
struct value_data {TYPE_1__* e; } ;
struct TYPE_2__ {unsigned int oldest_regno; unsigned int next_regno; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int INVALID_REGNUM ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  validate_value_data (struct value_data*) ; 

__attribute__((used)) static void
kill_value_one_regno (unsigned int regno, struct value_data *vd)
{
  unsigned int i, next;

  if (vd->e[regno].oldest_regno != regno)
    {
      for (i = vd->e[regno].oldest_regno;
	   vd->e[i].next_regno != regno;
	   i = vd->e[i].next_regno)
	continue;
      vd->e[i].next_regno = vd->e[regno].next_regno;
    }
  else if ((next = vd->e[regno].next_regno) != INVALID_REGNUM)
    {
      for (i = next; i != INVALID_REGNUM; i = vd->e[i].next_regno)
	vd->e[i].oldest_regno = next;
    }

  vd->e[regno].mode = VOIDmode;
  vd->e[regno].oldest_regno = regno;
  vd->e[regno].next_regno = INVALID_REGNUM;

#ifdef ENABLE_CHECKING
  validate_value_data (vd);
#endif
}