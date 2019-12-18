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
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 char* GenerateBackupNameForProcCollision (int /*<<< orphan*/  const*) ; 
 char* GenerateBackupNameForTypeCollision (int /*<<< orphan*/  const*) ; 
#define  OCLASS_PROC 129 
#define  OCLASS_TYPE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int getObjectClass (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static char *
GenerateBackupNameForCollision(const ObjectAddress *address)
{
	switch (getObjectClass(address))
	{
		case OCLASS_PROC:
		{
			return GenerateBackupNameForProcCollision(address);
		}

		case OCLASS_TYPE:
		{
			return GenerateBackupNameForTypeCollision(address);
		}

		default:
		{
			ereport(ERROR, (errmsg("unsupported object to construct a rename statement"),
							errdetail(
								"unable to generate a backup name for the old type")));
		}
	}
}