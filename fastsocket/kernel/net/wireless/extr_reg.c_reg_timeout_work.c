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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DBG_PRINT (char*) ; 
 int /*<<< orphan*/  restore_regulatory_settings (int) ; 

__attribute__((used)) static void reg_timeout_work(struct work_struct *work)
{
	REG_DBG_PRINT("Timeout while waiting for CRDA to reply, restoring regulatory settings\n");
	restore_regulatory_settings(true);
}