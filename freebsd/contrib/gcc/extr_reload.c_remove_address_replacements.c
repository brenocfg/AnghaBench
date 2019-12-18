#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_4__ {size_t what; int /*<<< orphan*/  where; } ;
struct TYPE_3__ {scalar_t__ in; } ;

/* Variables and functions */
 int MAX_RELOADS ; 
 int /*<<< orphan*/  deallocate_reload_reg (int) ; 
 scalar_t__ loc_mentioned_in_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int n_reloads ; 
 int n_replacements ; 
 TYPE_2__* replacements ; 
 TYPE_1__* rld ; 

int
remove_address_replacements (rtx in_rtx)
{
  int i, j;
  char reload_flags[MAX_RELOADS];
  int something_changed = 0;

  memset (reload_flags, 0, sizeof reload_flags);
  for (i = 0, j = 0; i < n_replacements; i++)
    {
      if (loc_mentioned_in_p (replacements[i].where, in_rtx))
	reload_flags[replacements[i].what] |= 1;
      else
	{
	  replacements[j++] = replacements[i];
	  reload_flags[replacements[i].what] |= 2;
	}
    }
  /* Note that the following store must be done before the recursive calls.  */
  n_replacements = j;

  for (i = n_reloads - 1; i >= 0; i--)
    {
      if (reload_flags[i] == 1)
	{
	  deallocate_reload_reg (i);
	  remove_address_replacements (rld[i].in);
	  rld[i].in = 0;
	  something_changed = 1;
	}
    }
  return something_changed;
}