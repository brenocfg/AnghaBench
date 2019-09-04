#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* Session; int /*<<< orphan*/  CancelList; int /*<<< orphan*/  IpPacketQueue; } ;
struct TYPE_5__ {int /*<<< orphan*/  Cancel1; } ;
typedef  int /*<<< orphan*/  L3PACKET ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  AddCancelList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void L3StoreIpPacketToIf(L3IF *src_if, L3IF *dst_if, L3PACKET *p)
{
	// Validate arguments
	if (src_if == NULL || p == NULL || dst_if == NULL)
	{
		return;
	}

	// Add to the queue of store-destination session
	InsertQueue(dst_if->IpPacketQueue, p);

	// Hit the Cancel object of the store-destination session
	AddCancelList(src_if->CancelList, dst_if->Session->Cancel1);
}