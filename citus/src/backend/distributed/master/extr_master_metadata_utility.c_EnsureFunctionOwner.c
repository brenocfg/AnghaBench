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
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_func_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_proc_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
EnsureFunctionOwner(Oid functionId)
{
	if (!pg_proc_ownercheck(functionId, GetUserId()))
	{
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_FUNCTION,
					   get_func_name(functionId));
	}
}