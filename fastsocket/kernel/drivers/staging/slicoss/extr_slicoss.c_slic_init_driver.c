#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ driver_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  slic_debug_init () ; 
 scalar_t__ slic_first_init ; 
 TYPE_2__ slic_global ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slic_init_driver(void)
{
	if (slic_first_init) {
		slic_first_init = 0;
		spin_lock_init(&slic_global.driver_lock.lock);
		slic_debug_init();
	}
}