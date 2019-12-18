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
typedef  int int32 ;
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  RESERVED_HASHED_COLUMN_ID ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Var *
MakeInt4Column()
{
	Index tableId = 0;
	AttrNumber columnAttributeNumber = RESERVED_HASHED_COLUMN_ID;
	Oid columnType = INT4OID;
	int32 columnTypeMod = -1;
	Oid columnCollationOid = InvalidOid;
	Index columnLevelSup = 0;

	Var *int4Column = makeVar(tableId, columnAttributeNumber, columnType,
							  columnTypeMod, columnCollationOid, columnLevelSup);
	return int4Column;
}