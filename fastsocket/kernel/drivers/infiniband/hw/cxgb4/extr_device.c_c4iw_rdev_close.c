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
struct c4iw_rdev {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_destroy_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_pblpool_destroy (struct c4iw_rdev*) ; 
 int /*<<< orphan*/  c4iw_rqtpool_destroy (struct c4iw_rdev*) ; 

__attribute__((used)) static void c4iw_rdev_close(struct c4iw_rdev *rdev)
{
	c4iw_pblpool_destroy(rdev);
	c4iw_rqtpool_destroy(rdev);
	c4iw_destroy_resource(&rdev->resource);
}