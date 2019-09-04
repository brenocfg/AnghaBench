#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * Tail; scalar_t__ NumPacketQueue; int /*<<< orphan*/ * PacketQueue; int /*<<< orphan*/  PacketQueueLock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NeoNewLock () ; 
 TYPE_1__* ctx ; 

void NeoInitPacketQueue()
{
	// Create a lock
	ctx->PacketQueueLock = NeoNewLock();
	// Initialize the packet queue
	ctx->PacketQueue = NULL;
	ctx->NumPacketQueue = 0;
	ctx->Tail = NULL;
}