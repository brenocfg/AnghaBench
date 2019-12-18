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
 int /*<<< orphan*/  CitusFunctionOidWithSignature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  WORKER_PARTIAL_AGGREGATE_NAME ; 

__attribute__((used)) static Oid
WorkerPartialAggOid()
{
	Oid argtypes[] = {
		OIDOID,
		ANYELEMENTOID,
	};

	return CitusFunctionOidWithSignature(WORKER_PARTIAL_AGGREGATE_NAME, 2, argtypes);
}