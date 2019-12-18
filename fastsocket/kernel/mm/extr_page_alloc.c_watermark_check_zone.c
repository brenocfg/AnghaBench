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
struct zone {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  low_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watermark_wq ; 
 scalar_t__ zone_watermark_ok (struct zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void watermark_check_zone(struct zone *zone)
{
	/* If no process is waiting, nothing to do */
	if (likely(!waitqueue_active(&watermark_wq)))
		return;

	/* Check if the high watermark is ok for order 0 */
	if (zone_watermark_ok(zone, 0, low_wmark_pages(zone), 0, 0))
		wake_up_interruptible(&watermark_wq);
}