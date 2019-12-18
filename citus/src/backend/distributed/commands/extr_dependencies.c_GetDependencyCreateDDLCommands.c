#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  objectId; } ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreateFunctionDDLCommandsIdempotent (TYPE_1__ const*) ; 
 char* CreateSchemaDDLCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateTypeDDLCommandsIdempotent (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
#define  OCLASS_CLASS 131 
#define  OCLASS_PROC 130 
#define  OCLASS_SCHEMA 129 
#define  OCLASS_TYPE 128 
 int /*<<< orphan*/  RELKIND_COMPOSITE_TYPE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int getObjectClass (TYPE_1__ const*) ; 
 int /*<<< orphan*/  getObjectTypeDescription (TYPE_1__ const*) ; 
 int /*<<< orphan*/  get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (void*) ; 

__attribute__((used)) static List *
GetDependencyCreateDDLCommands(const ObjectAddress *dependency)
{
	switch (getObjectClass(dependency))
	{
		case OCLASS_CLASS:
		{
			/*
			 * types have an intermediate dependency on a relation (aka class), so we do
			 * support classes when the relkind is composite
			 */
			if (get_rel_relkind(dependency->objectId) == RELKIND_COMPOSITE_TYPE)
			{
				return NIL;
			}

			/* if this relation is not supported, break to the error at the end */
			break;
		}

		case OCLASS_PROC:
		{
			return CreateFunctionDDLCommandsIdempotent(dependency);
		}

		case OCLASS_SCHEMA:
		{
			const char *schemaDDLCommand = CreateSchemaDDLCommand(dependency->objectId);

			if (schemaDDLCommand == NULL)
			{
				/* no schema to create */
				return NIL;
			}

			return list_make1((void *) schemaDDLCommand);
		}

		case OCLASS_TYPE:
		{
			return CreateTypeDDLCommandsIdempotent(dependency);
		}

		default:
		{
			break;
		}
	}

	/*
	 * make sure it fails hard when in debug mode, leave a hint for the user if this ever
	 * happens in production
	 */
	Assert(false);
	ereport(ERROR, (errmsg("unsupported object %s for distribution by citus",
						   getObjectTypeDescription(dependency)),
					errdetail(
						"citus tries to recreate an unsupported object on its workers"),
					errhint("please report a bug as this should not be happening")));
}