#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int YUI_IS_RUNNING ; 
 scalar_t__ gtk_main_iteration () ; 
 TYPE_1__* yui ; 

__attribute__((used)) static void debugPauseLoop(void) { /* secondary gtk event loop for the "breakpoint pause" state */

  while ( !(yui->state & YUI_IS_RUNNING) )
    if ( gtk_main_iteration() ) return;
}