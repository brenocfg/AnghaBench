#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* impl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Name ) () ;} ;
typedef  TYPE_2__ PROTO ;

/* Variables and functions */
 scalar_t__ StrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int ProtoCompare(void *p1, void *p2)
{
	PROTO *proto_1, *proto_2;

	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}

	proto_1 = (PROTO *)p1;
	proto_2 = (PROTO *)p2;

	if (StrCmp(proto_1->impl->Name(), proto_2->impl->Name()) == 0)
	{
		return true;
	}

	return false;
}