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
 scalar_t__ S3C2410_WTCNT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wdt_base ; 
 int /*<<< orphan*/  wdt_count ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s3c2410wdt_keepalive(void)
{
	spin_lock(&wdt_lock);
	writel(wdt_count, wdt_base + S3C2410_WTCNT);
	spin_unlock(&wdt_lock);
}