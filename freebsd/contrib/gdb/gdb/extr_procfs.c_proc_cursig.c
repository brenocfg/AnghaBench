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
struct TYPE_3__ {long pr_cursig; } ;
struct TYPE_4__ {long pr_cursig; TYPE_1__ pr_lwp; } ;
struct procinfo {TYPE_2__ prstatus; int /*<<< orphan*/  status_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_get_status (struct procinfo*) ; 

long
proc_cursig (struct procinfo *pi)
{
  if (!pi->status_valid)
    if (!proc_get_status (pi))
      return 0;	/* FIXME: not a good failure value (but what is?) */

#ifdef NEW_PROC_API
  return pi->prstatus.pr_lwp.pr_cursig;
#else
  return pi->prstatus.pr_cursig;
#endif
}