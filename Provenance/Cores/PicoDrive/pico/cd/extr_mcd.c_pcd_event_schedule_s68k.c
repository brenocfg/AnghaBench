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
typedef  enum pcd_event { ____Placeholder_pcd_event } pcd_event ;

/* Variables and functions */
 int /*<<< orphan*/  SekCyclesDoneS68k () ; 
 int SekCyclesLeftS68k ; 
 int /*<<< orphan*/  SekEndRunS68k (int) ; 
 int /*<<< orphan*/  pcd_event_schedule (int /*<<< orphan*/ ,int,int) ; 

void pcd_event_schedule_s68k(enum pcd_event event, int after)
{
  if (SekCyclesLeftS68k > after)
    SekEndRunS68k(after);

  pcd_event_schedule(SekCyclesDoneS68k(), event, after);
}