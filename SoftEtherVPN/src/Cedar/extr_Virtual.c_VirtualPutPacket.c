#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flag1; int /*<<< orphan*/  Now; TYPE_1__* NativeNat; } ;
typedef  TYPE_2__ VH ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {int /*<<< orphan*/  Ref; } ;
struct TYPE_10__ {int SendStateChanged; int /*<<< orphan*/  Lock; TYPE_3__* HaltTube; } ;
typedef  TYPE_3__ TUBE ;
typedef  int /*<<< orphan*/  PKT ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreePacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/ * ParsePacket (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTube (TYPE_3__*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  TubeFlushEx (TYPE_3__*,int) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/  VirtualLayer2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

bool VirtualPutPacket(VH *v, void *data, UINT size)
{
	if (data == NULL)
	{
		// Flush
		v->flag1 = false;

		if (v->NativeNat != NULL)
		{
			if (v->NativeNat->SendStateChanged)
			{
				TUBE *halt_tube = NULL;

				Lock(v->NativeNat->Lock);
				{
					if (v->NativeNat->HaltTube != NULL)
					{
						halt_tube = v->NativeNat->HaltTube;

						AddRef(halt_tube->Ref);
					}
				}
				Unlock(v->NativeNat->Lock);

				if (halt_tube != NULL)
				{
					TubeFlushEx(halt_tube, true);

					v->NativeNat->SendStateChanged = false;

					ReleaseTube(halt_tube);
				}
			}
		}
	}
	else
	{
		// Interpret the received packet
		PKT *packet = ParsePacket(data, size);

		if (v->flag1 == false)
		{
			v->flag1 = true;
			v->Now = Tick64();
		}

		// Lock the entire virtual machine in here
		LockVirtual(v);
		{
			if (packet != NULL)
			{
				// Process the Layer-2
				VirtualLayer2(v, packet);

				// Release the packet structure
				FreePacket(packet);
			}
		}
		UnlockVirtual(v);

		Free(data);
	}

	return true;
}