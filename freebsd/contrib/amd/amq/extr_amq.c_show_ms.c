#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int as_drops; int as_stale; int as_mok; int as_merr; int as_uerr; } ;
typedef  TYPE_1__ amq_mount_stats ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 

__attribute__((used)) static void
show_ms(amq_mount_stats *ms)
{
  printf("\
requests  stale     mount     mount     unmount\n\
deferred  fhandles  ok        failed    failed\n\
%-9d %-9d %-9d %-9d %-9d\n",
	 ms->as_drops, ms->as_stale, ms->as_mok, ms->as_merr, ms->as_uerr);
}