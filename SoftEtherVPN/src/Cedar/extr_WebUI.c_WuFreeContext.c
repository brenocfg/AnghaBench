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
struct TYPE_4__ {struct TYPE_4__* Admin; struct TYPE_4__* HubName; struct TYPE_4__* Rpc; int /*<<< orphan*/  Lock; } ;
typedef  TYPE_1__ WU_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

__attribute__((used)) static void WuFreeContext(WU_CONTEXT *context)
{
	DeleteLock(context->Admin->Rpc->Lock);
	Free(context->Admin->Rpc);
	Free(context->Admin->HubName);
	Free(context->Admin);
	Free(context);
}