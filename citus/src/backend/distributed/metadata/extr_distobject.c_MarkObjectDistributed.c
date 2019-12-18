#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int ExecuteCommandAsSuperuser (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
MarkObjectDistributed(const ObjectAddress *distAddress)
{
	int paramCount = 3;
	Oid paramTypes[3] = {
		OIDOID,
		OIDOID,
		INT4OID
	};
	Datum paramValues[3] = {
		ObjectIdGetDatum(distAddress->classId),
		ObjectIdGetDatum(distAddress->objectId),
		Int32GetDatum(distAddress->objectSubId)
	};
	int spiStatus = 0;

	char *insertQuery = "INSERT INTO citus.pg_dist_object (classid, objid, objsubid) "
						"VALUES ($1, $2, $3) ON CONFLICT DO NOTHING";

	spiStatus = ExecuteCommandAsSuperuser(insertQuery, paramCount, paramTypes,
										  paramValues);
	if (spiStatus < 0)
	{
		ereport(ERROR, (errmsg("failed to insert object into citus.pg_dist_object")));
	}
}