#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* generate_qualified_relation_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

char *
ColocationIdUpdateCommand(Oid relationId, uint32 colocationId)
{
	StringInfo command = makeStringInfo();
	char *qualifiedRelationName = generate_qualified_relation_name(relationId);
	appendStringInfo(command, "UPDATE pg_dist_partition "
							  "SET colocationid = %d "
							  "WHERE logicalrelid = %s::regclass",
					 colocationId, quote_literal_cstr(qualifiedRelationName));

	return command->data;
}