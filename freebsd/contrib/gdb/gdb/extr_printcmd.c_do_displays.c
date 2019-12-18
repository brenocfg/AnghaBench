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
struct display {struct display* next; } ;

/* Variables and functions */
 struct display* display_chain ; 
 int /*<<< orphan*/  do_one_display (struct display*) ; 

void
do_displays (void)
{
  struct display *d;

  for (d = display_chain; d; d = d->next)
    do_one_display (d);
}