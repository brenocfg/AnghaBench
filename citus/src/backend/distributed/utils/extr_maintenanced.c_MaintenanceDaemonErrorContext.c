#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  userOid; int /*<<< orphan*/  databaseOid; } ;
typedef  TYPE_1__ MaintenanceDaemonDBData ;

/* Variables and functions */
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MaintenanceDaemonErrorContext(void *arg)
{
	MaintenanceDaemonDBData *myDbData = (MaintenanceDaemonDBData *) arg;
	errcontext("Citus maintenance daemon for database %u user %u",
			   myDbData->databaseOid, myDbData->userOid);
}