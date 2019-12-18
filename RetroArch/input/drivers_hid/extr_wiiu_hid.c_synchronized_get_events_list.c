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
typedef  int /*<<< orphan*/  wiiu_attach_event ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ SwapAtomic32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ events ; 

__attribute__((used)) static wiiu_attach_event *synchronized_get_events_list(void)
{
   return (wiiu_attach_event *)SwapAtomic32((uint32_t *)&events.list, 0);
}