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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * impl; } ;
typedef  int /*<<< orphan*/  PROTO_IMPL ;
typedef  TYPE_1__ PROTO ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* ProtoGet (scalar_t__) ; 
 scalar_t__ ProtoNum () ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * protocols ; 

void ProtoFree()
{
	UINT i;
	PROTO_IMPL *impl;

	for (i = 0; i < ProtoNum(); ++i)
	{
		PROTO *proto = ProtoGet(i);
		impl = proto->impl;
		Free(proto);
	}

	ReleaseList(protocols);
	protocols = NULL;
}