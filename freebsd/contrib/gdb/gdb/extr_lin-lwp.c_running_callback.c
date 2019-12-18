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
struct lwp_info {scalar_t__ stopped; scalar_t__ status; scalar_t__ resumed; } ;

/* Variables and functions */

__attribute__((used)) static int
running_callback (struct lwp_info *lp, void *data)
{
  return (lp->stopped == 0 || (lp->status != 0 && lp->resumed));
}