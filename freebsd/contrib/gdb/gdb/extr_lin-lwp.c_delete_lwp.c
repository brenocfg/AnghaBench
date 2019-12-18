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
struct lwp_info {struct lwp_info* next; int /*<<< orphan*/  ptid; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 struct lwp_info* lwp_list ; 
 int /*<<< orphan*/  num_lwps ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct lwp_info*) ; 

__attribute__((used)) static void
delete_lwp (ptid_t ptid)
{
  struct lwp_info *lp, *lpprev;

  lpprev = NULL;

  for (lp = lwp_list; lp; lpprev = lp, lp = lp->next)
    if (ptid_equal (lp->ptid, ptid))
      break;

  if (!lp)
    return;

  /* We don't go back to "non-threaded" mode if the number of threads
     becomes less than two.  */
  num_lwps--;

  if (lpprev)
    lpprev->next = lp->next;
  else
    lwp_list = lp->next;

  xfree (lp);
}