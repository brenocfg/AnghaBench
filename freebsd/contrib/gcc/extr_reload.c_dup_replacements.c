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
struct replacement {int /*<<< orphan*/  mode; int /*<<< orphan*/  what; int /*<<< orphan*/ * where; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int n_replacements ; 
 int /*<<< orphan*/  push_replacement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct replacement* replacements ; 

__attribute__((used)) static void
dup_replacements (rtx *dup_loc, rtx *orig_loc)
{
  int i, n = n_replacements;

  for (i = 0; i < n; i++)
    {
      struct replacement *r = &replacements[i];
      if (r->where == orig_loc)
	push_replacement (dup_loc, r->what, r->mode);
    }
}