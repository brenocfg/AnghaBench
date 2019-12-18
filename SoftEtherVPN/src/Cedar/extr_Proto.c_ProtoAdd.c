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
struct TYPE_7__ {TYPE_1__* impl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Name ) () ;} ;
typedef  TYPE_1__ PROTO_IMPL ;
typedef  TYPE_2__ PROTO ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* Malloc (int) ; 
 int /*<<< orphan*/ * protocols ; 
 int /*<<< orphan*/  stub1 () ; 

bool ProtoAdd(PROTO_IMPL *impl)
{
	PROTO *proto;

	if (protocols == NULL || impl == NULL)
	{
		return false;
	}

	proto = Malloc(sizeof(PROTO));
	proto->impl = impl;

	Add(protocols, proto);

	Debug("ProtoAdd(): added %s\n", proto->impl->Name());

	return true;
}