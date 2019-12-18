#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_10__ {TYPE_1__* relation; } ;
struct TYPE_9__ {int /*<<< orphan*/  connectionList; int /*<<< orphan*/  shardId; } ;
struct TYPE_8__ {char* relname; char* schemaname; } ;
typedef  TYPE_2__ ShardConnections ;
typedef  TYPE_3__ CopyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  MasterCreateEmptyShard (char*) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OpenCopyConnectionsForNewShards (TYPE_3__*,TYPE_2__*,int,int) ; 
 char* quote_qualified_identifier (char*,char*) ; 

__attribute__((used)) static int64
StartCopyToNewShard(ShardConnections *shardConnections, CopyStmt *copyStatement,
					bool useBinaryCopyFormat)
{
	char *relationName = copyStatement->relation->relname;
	char *schemaName = copyStatement->relation->schemaname;
	char *qualifiedName = quote_qualified_identifier(schemaName, relationName);
	int64 shardId = MasterCreateEmptyShard(qualifiedName);
	bool stopOnFailure = true;

	shardConnections->shardId = shardId;

	shardConnections->connectionList = NIL;

	/* connect to shards placements and start transactions */
	OpenCopyConnectionsForNewShards(copyStatement, shardConnections, stopOnFailure,
									useBinaryCopyFormat);

	return shardId;
}