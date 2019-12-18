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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char TRANSFER_MODE_AUTOMATIC ; 
 char TRANSFER_MODE_BLOCK_WRITES ; 
 char TRANSFER_MODE_FORCE_LOGICAL ; 
 int /*<<< orphan*/  enum_out ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char
LookupShardTransferMode(Oid shardReplicationModeOid)
{
	char shardReplicationMode = 0;

	Datum enumLabelDatum = DirectFunctionCall1(enum_out, shardReplicationModeOid);
	char *enumLabel = DatumGetCString(enumLabelDatum);

	if (strncmp(enumLabel, "auto", NAMEDATALEN) == 0)
	{
		shardReplicationMode = TRANSFER_MODE_AUTOMATIC;
	}
	else if (strncmp(enumLabel, "force_logical", NAMEDATALEN) == 0)
	{
		shardReplicationMode = TRANSFER_MODE_FORCE_LOGICAL;
	}
	else if (strncmp(enumLabel, "block_writes", NAMEDATALEN) == 0)
	{
		shardReplicationMode = TRANSFER_MODE_BLOCK_WRITES;
	}
	else
	{
		ereport(ERROR, (errmsg("invalid label for enum: %s", enumLabel)));
	}

	return shardReplicationMode;
}