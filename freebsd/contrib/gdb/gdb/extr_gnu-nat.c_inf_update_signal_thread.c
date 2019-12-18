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
struct inf {TYPE_1__* threads; int /*<<< orphan*/  signal_thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */

__attribute__((used)) static void
inf_update_signal_thread (struct inf *inf)
{
  /* XXX for now we assume that if there's a msgport, the 2nd thread is
     the signal thread.  */
  inf->signal_thread = inf->threads ? inf->threads->next : 0;
}