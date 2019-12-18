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
struct replacement {int what; int mode; scalar_t__ subreg_loc; int /*<<< orphan*/ * where; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  n_replacements ; 
 scalar_t__ replace_reloads ; 
 struct replacement* replacements ; 

__attribute__((used)) static void
push_replacement (rtx *loc, int reloadnum, enum machine_mode mode)
{
  if (replace_reloads)
    {
      struct replacement *r = &replacements[n_replacements++];
      r->what = reloadnum;
      r->where = loc;
      r->subreg_loc = 0;
      r->mode = mode;
    }
}