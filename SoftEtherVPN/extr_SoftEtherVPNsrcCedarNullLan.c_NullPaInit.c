#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  PacketGeneratorThread; scalar_t__ Id; int /*<<< orphan*/  MacAddr; int /*<<< orphan*/  Event; int /*<<< orphan*/  PacketQueue; int /*<<< orphan*/  Cancel; } ;
struct TYPE_8__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_7__ {void* Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ NULL_LAN ;

/* Variables and functions */
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  NullGenerateMacAddress (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NullPacketGenerateThread ; 
 TYPE_3__* ZeroMalloc (int) ; 

bool NullPaInit(SESSION *s)
{
	NULL_LAN *n;
	static UINT id_seed = 0;
	// Validate arguments
	if (s == NULL)
	{
		return false;
	}

	id_seed++;

	n = ZeroMalloc(sizeof(NULL_LAN));
	n->Id = id_seed;
	s->PacketAdapter->Param = (void *)n;

	n->Cancel = NewCancel();
	n->PacketQueue = NewQueue();
	n->Event = NewEvent();

	NullGenerateMacAddress(n->MacAddr, n->Id, 0);

	n->PacketGeneratorThread = NewThread(NullPacketGenerateThread, n);

	return true;
}