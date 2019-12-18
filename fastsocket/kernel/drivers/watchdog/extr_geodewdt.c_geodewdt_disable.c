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
 int /*<<< orphan*/  MFGPT_REG_COUNTER ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int /*<<< orphan*/  geode_mfgpt_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_timer ; 

__attribute__((used)) static void geodewdt_disable(void)
{
	geode_mfgpt_write(wdt_timer, MFGPT_REG_SETUP, 0);
	geode_mfgpt_write(wdt_timer, MFGPT_REG_COUNTER, 0);
}