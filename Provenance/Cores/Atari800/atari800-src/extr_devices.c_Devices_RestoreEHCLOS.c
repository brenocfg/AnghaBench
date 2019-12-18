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
 int /*<<< orphan*/  ESC_EHCLOS ; 
 int /*<<< orphan*/  ehclos_addr ; 

__attribute__((used)) static void Devices_RestoreEHCLOS(void)
{
	Devices_RestoreHandler(ehclos_addr, ESC_EHCLOS);
}