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
struct inf {int /*<<< orphan*/  task; int /*<<< orphan*/  threads_up_to_date; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_validate_procs (struct inf*) ; 

int
inf_update_procs (struct inf *inf)
{
  if (!inf->task)
    return 0;
  if (!inf->threads_up_to_date)
    inf_validate_procs (inf);
  return !!inf->task;
}