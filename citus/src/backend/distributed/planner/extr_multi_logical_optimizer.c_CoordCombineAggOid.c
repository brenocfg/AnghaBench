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

/* Variables and functions */
 int /*<<< orphan*/  ANYELEMENTOID ; 
 int /*<<< orphan*/  COORD_COMBINE_AGGREGATE_NAME ; 
 int /*<<< orphan*/  CSTRINGOID ; 
 int /*<<< orphan*/  CitusFunctionOidWithSignature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OIDOID ; 

__attribute__((used)) static Oid
CoordCombineAggOid()
{
	Oid argtypes[] = {
		OIDOID,
		CSTRINGOID,
		ANYELEMENTOID,
	};

	return CitusFunctionOidWithSignature(COORD_COMBINE_AGGREGATE_NAME, 3, argtypes);
}