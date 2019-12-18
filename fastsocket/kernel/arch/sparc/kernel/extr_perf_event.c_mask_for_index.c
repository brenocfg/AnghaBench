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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  event_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_encoding (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sparc_pmu ; 

__attribute__((used)) static u64 mask_for_index(int idx)
{
	return event_encoding(sparc_pmu->event_mask, idx);
}