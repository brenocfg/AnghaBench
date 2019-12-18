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
struct breakpoint {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ bp_catch_load ; 
 scalar_t__ bp_catch_unload ; 

int
ep_is_shlib_catchpoint (struct breakpoint *ep)
{
  return
    (ep->type == bp_catch_load)
    || (ep->type == bp_catch_unload);
}