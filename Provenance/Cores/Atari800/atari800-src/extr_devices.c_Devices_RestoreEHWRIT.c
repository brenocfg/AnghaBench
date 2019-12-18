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
 int /*<<< orphan*/  Devices_RestoreHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_EHWRIT ; 
 int /*<<< orphan*/  ehwrit_addr ; 

__attribute__((used)) static void Devices_RestoreEHWRIT(void)
{
	Devices_RestoreHandler(ehwrit_addr, ESC_EHWRIT);
}