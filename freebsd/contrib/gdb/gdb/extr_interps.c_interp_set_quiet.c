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
struct interp {int quiet_p; } ;

/* Variables and functions */

__attribute__((used)) static int
interp_set_quiet (struct interp *interp, int quiet)
{
  int old_val = interp->quiet_p;
  interp->quiet_p = quiet;
  return old_val;
}