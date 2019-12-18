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
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_lwp (int /*<<< orphan*/ ) ; 
 struct lwp_info* lwp_list ; 
 int /*<<< orphan*/  memset (struct lwp_info*,int /*<<< orphan*/ ,int) ; 
 int num_lwps ; 
 int threaded ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct lwp_info *
add_lwp (ptid_t ptid)
{
  struct lwp_info *lp;

  gdb_assert (is_lwp (ptid));

  lp = (struct lwp_info *) xmalloc (sizeof (struct lwp_info));

  memset (lp, 0, sizeof (struct lwp_info));

  lp->ptid = ptid;

  lp->next = lwp_list;
  lwp_list = lp;
  if (++num_lwps > 1)
    threaded = 1;

  return lp;
}