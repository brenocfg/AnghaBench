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
struct reg_write_state {int write_count; int first_pred; int /*<<< orphan*/  written_by_or; int /*<<< orphan*/  written_by_and; int /*<<< orphan*/  written_by_fp; } ;
struct reg_flags {int /*<<< orphan*/  is_or; int /*<<< orphan*/  is_and; int /*<<< orphan*/  is_fp; } ;

/* Variables and functions */

__attribute__((used)) static void
rws_update (struct reg_write_state *rws, int regno, struct reg_flags flags, int pred)
{
  if (pred)
    rws[regno].write_count++;
  else
    rws[regno].write_count = 2;
  rws[regno].written_by_fp |= flags.is_fp;
  /* ??? Not tracking and/or across differing predicates.  */
  rws[regno].written_by_and = flags.is_and;
  rws[regno].written_by_or = flags.is_or;
  rws[regno].first_pred = pred;
}