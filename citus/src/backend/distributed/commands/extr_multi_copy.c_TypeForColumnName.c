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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/  atttypid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 TYPE_1__* TupleDescAttr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ get_attnum (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Oid
TypeForColumnName(Oid relationId, TupleDesc tupleDescriptor, char *columnName)
{
	AttrNumber destAttrNumber = get_attnum(relationId, columnName);
	Form_pg_attribute attr = NULL;

	if (destAttrNumber == InvalidAttrNumber)
	{
		ereport(ERROR, (errmsg("invalid attr? %s", columnName)));
	}

	attr = TupleDescAttr(tupleDescriptor, destAttrNumber - 1);
	return attr->atttypid;
}