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
struct TYPE_2__ {scalar_t__ end_jiffies; int /*<<< orphan*/  start_jiffies; } ;
struct raid_set {TYPE_1__ recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void set_start_recovery(struct raid_set *rs)
{
	/* Initialize recovery. */
	rs->recover.start_jiffies = jiffies;
	rs->recover.end_jiffies = 0;
}