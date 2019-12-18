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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 TYPE_1__ sch311x_wdt_data ; 
 int /*<<< orphan*/  sch311x_wdt_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void sch311x_wdt_keepalive(void)
{
	spin_lock(&sch311x_wdt_data.io_lock);
	sch311x_wdt_set_timeout(timeout);
	spin_unlock(&sch311x_wdt_data.io_lock);
}