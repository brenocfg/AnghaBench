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
struct lwp_info {scalar_t__ status; scalar_t__ step; } ;

/* Variables and functions */

__attribute__((used)) static int
select_singlestep_lwp_callback (struct lwp_info *lp, void *data)
{
  if (lp->step && lp->status != 0)
    return 1;
  else
    return 0;
}