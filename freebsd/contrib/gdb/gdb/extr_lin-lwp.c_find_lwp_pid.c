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
struct lwp_info {int /*<<< orphan*/  ptid; struct lwp_info* next; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int GET_LWP (int /*<<< orphan*/ ) ; 
 int GET_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ is_lwp (int /*<<< orphan*/ ) ; 
 struct lwp_info* lwp_list ; 

__attribute__((used)) static struct lwp_info *
find_lwp_pid (ptid_t ptid)
{
  struct lwp_info *lp;
  int lwp;

  if (is_lwp (ptid))
    lwp = GET_LWP (ptid);
  else
    lwp = GET_PID (ptid);

  for (lp = lwp_list; lp; lp = lp->next)
    if (lwp == GET_LWP (lp->ptid))
      return lp;

  return NULL;
}