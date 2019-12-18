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
struct linear_c {int /*<<< orphan*/  dev; } ;
struct dm_target {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct linear_c*) ; 

__attribute__((used)) static void linear_dtr(struct dm_target *ti)
{
	struct linear_c *lc = (struct linear_c *) ti->private;

	dm_put_device(ti, lc->dev);
	kfree(lc);
}