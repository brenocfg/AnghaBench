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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/ * subreg_loc; int /*<<< orphan*/ * where; } ;

/* Variables and functions */
 int n_replacements ; 
 TYPE_1__* replacements ; 

void
move_replacements (rtx *x, rtx *y)
{
  int i;

  for (i = 0; i < n_replacements; i++)
    if (replacements[i].subreg_loc == x)
      replacements[i].subreg_loc = y;
    else if (replacements[i].where == x)
      {
	replacements[i].where = y;
	replacements[i].subreg_loc = 0;
      }
}