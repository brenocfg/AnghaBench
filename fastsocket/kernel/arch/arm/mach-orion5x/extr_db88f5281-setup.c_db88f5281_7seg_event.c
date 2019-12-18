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
 int HZ ; 
 scalar_t__ db88f5281_7seg ; 
 int /*<<< orphan*/  db88f5281_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void db88f5281_7seg_event(unsigned long data)
{
	static int count = 0;
	writel(0, db88f5281_7seg + (count << 4));
	count = (count + 1) & 7;
	mod_timer(&db88f5281_timer, jiffies + 2 * HZ);
}