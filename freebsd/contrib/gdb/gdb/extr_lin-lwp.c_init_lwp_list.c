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
struct lwp_info {struct lwp_info* next; } ;

/* Variables and functions */
 struct lwp_info* lwp_list ; 
 scalar_t__ num_lwps ; 
 scalar_t__ threaded ; 
 int /*<<< orphan*/  xfree (struct lwp_info*) ; 

__attribute__((used)) static void
init_lwp_list (void)
{
  struct lwp_info *lp, *lpnext;

  for (lp = lwp_list; lp; lp = lpnext)
    {
      lpnext = lp->next;
      xfree (lp);
    }

  lwp_list = NULL;
  num_lwps = 0;
  threaded = 0;
}