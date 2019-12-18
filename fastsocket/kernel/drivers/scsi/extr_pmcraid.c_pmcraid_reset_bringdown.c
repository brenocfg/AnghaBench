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
struct pmcraid_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOA_STATE_UNKNOWN ; 
 int /*<<< orphan*/  SHUTDOWN_NORMAL ; 
 int pmcraid_reset_reload (struct pmcraid_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmcraid_reset_bringdown(struct pmcraid_instance *pinstance)
{
	return pmcraid_reset_reload(pinstance,
				    SHUTDOWN_NORMAL,
				    IOA_STATE_UNKNOWN);
}