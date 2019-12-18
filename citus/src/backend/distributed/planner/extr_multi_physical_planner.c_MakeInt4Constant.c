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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * makeConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

Const *
MakeInt4Constant(Datum constantValue)
{
	Oid constantType = INT4OID;
	int32 constantTypeMode = -1;
	Oid constantCollationId = InvalidOid;
	int constantLength = sizeof(int32);
	bool constantIsNull = false;
	bool constantByValue = true;

	Const *int4Constant = makeConst(constantType, constantTypeMode, constantCollationId,
									constantLength, constantValue, constantIsNull,
									constantByValue);
	return int4Constant;
}