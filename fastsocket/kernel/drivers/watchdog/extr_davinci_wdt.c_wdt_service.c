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

/* Variables and functions */
 int /*<<< orphan*/  WDKEY_SEQ0 ; 
 int /*<<< orphan*/  WDKEY_SEQ1 ; 
 scalar_t__ WDTCR ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wdt_base ; 

__attribute__((used)) static void wdt_service(void)
{
	spin_lock(&io_lock);

	/* put watchdog in service state */
	iowrite32(WDKEY_SEQ0, wdt_base + WDTCR);
	/* put watchdog in active state */
	iowrite32(WDKEY_SEQ1, wdt_base + WDTCR);

	spin_unlock(&io_lock);
}