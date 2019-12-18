#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int classid; int refclassid; void* deptype; int /*<<< orphan*/  refobjsubid; int /*<<< orphan*/  refobjid; int /*<<< orphan*/  objsubid; int /*<<< orphan*/  objid; } ;
struct TYPE_6__ {int classId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  objectSubId; } ;
typedef  int /*<<< orphan*/  ObjectAddressCollector ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__* Form_pg_depend ;
typedef  int /*<<< orphan*/  FormData_pg_depend ;

/* Variables and functions */
 void* DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/ * NIL ; 
 int RelationRelationId ; 
 int /*<<< orphan*/  TYPTYPE_COMPOSITE ; 
#define  TypeRelationId 128 
 int /*<<< orphan*/  get_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typ_typrelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  type_is_array (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
ExpandCitusSupportedTypes(ObjectAddressCollector *collector, const ObjectAddress *target)
{
	List *result = NIL;

	switch (target->classId)
	{
		case TypeRelationId:
		{
			/*
			 * types depending on other types are not captured in pg_depend, instead they
			 * are described with their dependencies by the relation that describes the
			 * composite type.
			 */
			if (get_typtype(target->objectId) == TYPTYPE_COMPOSITE)
			{
				Form_pg_depend dependency = palloc0(sizeof(FormData_pg_depend));
				dependency->classid = target->classId;
				dependency->objid = target->objectId;
				dependency->objsubid = target->objectSubId;

				/* add outward edge to the type's relation */
				dependency->refclassid = RelationRelationId;
				dependency->refobjid = get_typ_typrelid(target->objectId);
				dependency->refobjsubid = 0;

				dependency->deptype = DEPENDENCY_NORMAL;

				result = lappend(result, dependency);
			}

			/*
			 * array types don't have a normal dependency on their element type, instead
			 * their dependency is an internal one. We can't follow interal dependencies
			 * as that would cause a cyclic dependency on others, instead we expand here
			 * to follow the dependency on the element type.
			 */
			if (type_is_array(target->objectId))
			{
				Form_pg_depend dependency = palloc0(sizeof(FormData_pg_depend));
				dependency->classid = target->classId;
				dependency->objid = target->objectId;
				dependency->objsubid = target->objectSubId;

				/* add outward edge to the element type */
				dependency->refclassid = TypeRelationId;
				dependency->refobjid = get_element_type(target->objectId);
				dependency->refobjsubid = 0;

				dependency->deptype = DEPENDENCY_NORMAL;

				result = lappend(result, dependency);
			}

			break;
		}

		default:
		{
			/* no expansion for unsupported types */
			break;
		}
	}
	return result;
}