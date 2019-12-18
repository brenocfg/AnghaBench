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
struct inferior_status {int /*<<< orphan*/  stop_registers; int /*<<< orphan*/  registers; int /*<<< orphan*/  stop_bpstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpstat_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct inferior_status*) ; 

void
discard_inferior_status (struct inferior_status *inf_status)
{
  /* See save_inferior_status for info on stop_bpstat. */
  bpstat_clear (&inf_status->stop_bpstat);
  regcache_xfree (inf_status->registers);
  regcache_xfree (inf_status->stop_registers);
  xfree (inf_status);
}