#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mt_device_t ;
struct TYPE_3__ {int /*<<< orphan*/  mtd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt_device_unlock(mt_device_t dev)
{
	lck_mtx_unlock(&dev->mtd_lock);
}