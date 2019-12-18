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
struct TYPE_4__ {int /*<<< orphan*/  objname; } ;
typedef  TYPE_1__ ObjectWithArgs ;
typedef  int /*<<< orphan*/  ObjectType ;

/* Variables and functions */
 int /*<<< orphan*/  DeconstructQualifiedName (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  QualifyFunctionSchemaName (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
QualifyFunction(ObjectWithArgs *func, ObjectType type)
{
	char *functionName = NULL;
	char *schemaName = NULL;

	/* check if the function name is already qualified */
	DeconstructQualifiedName(func->objname, &schemaName, &functionName);

	/* do a lookup for the schema name if the statement does not include one */
	if (schemaName == NULL)
	{
		QualifyFunctionSchemaName(func, type);
	}
}