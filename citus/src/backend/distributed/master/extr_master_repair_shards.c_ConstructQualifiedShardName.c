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
struct TYPE_3__ {int /*<<< orphan*/  shardId; int /*<<< orphan*/  relationId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AppendShardIdToName (char**,int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 char* quote_qualified_identifier (char*,char*) ; 

char *
ConstructQualifiedShardName(ShardInterval *shardInterval)
{
	Oid schemaId = get_rel_namespace(shardInterval->relationId);
	char *schemaName = get_namespace_name(schemaId);
	char *tableName = get_rel_name(shardInterval->relationId);
	char *shardName = NULL;

	shardName = pstrdup(tableName);
	AppendShardIdToName(&shardName, shardInterval->shardId);
	shardName = quote_qualified_identifier(schemaName, shardName);

	return shardName;
}