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

/* Variables and functions */
 scalar_t__ errorcount ; 
 scalar_t__ optimize ; 
 scalar_t__ sorrycount ; 

__attribute__((used)) static bool
gate_no_optimization (void)
{
  /* With errors, normal optimization passes are not run.  If we don't
     lower complex operations at all, rtl expansion will abort.  */
  return optimize == 0 || sorrycount || errorcount;
}