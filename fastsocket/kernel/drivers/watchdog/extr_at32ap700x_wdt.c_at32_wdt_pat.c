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
struct TYPE_3__ {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wdt ; 
 int /*<<< orphan*/  wdt_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void at32_wdt_pat(void)
{
	spin_lock(&wdt->io_lock);
	wdt_writel(wdt, CLR, 0x42);
	spin_unlock(&wdt->io_lock);
}