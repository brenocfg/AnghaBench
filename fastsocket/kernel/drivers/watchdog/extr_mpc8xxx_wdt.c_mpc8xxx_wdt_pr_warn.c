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
 int /*<<< orphan*/  pr_crit (char*,char const*,char*) ; 
 scalar_t__ reset ; 

__attribute__((used)) static void mpc8xxx_wdt_pr_warn(const char *msg)
{
	pr_crit("mpc8xxx_wdt: %s, expect the %s soon!\n", msg,
		reset ? "reset" : "machine check exception");
}