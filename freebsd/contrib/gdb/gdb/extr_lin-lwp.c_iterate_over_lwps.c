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
 int stub1 (struct lwp_info*,void*) ; 

struct lwp_info *
iterate_over_lwps (int (*callback) (struct lwp_info *, void *), void *data)
{
  struct lwp_info *lp, *lpnext;

  for (lp = lwp_list; lp; lp = lpnext)
    {
      lpnext = lp->next;
      if ((*callback) (lp, data))
	return lp;
    }

  return NULL;
}