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
struct dock_station {int /*<<< orphan*/  last_dock_time; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOCK_DOCKING ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void complete_dock(struct dock_station *ds)
{
	ds->flags &= ~(DOCK_DOCKING);
	ds->last_dock_time = jiffies;
}