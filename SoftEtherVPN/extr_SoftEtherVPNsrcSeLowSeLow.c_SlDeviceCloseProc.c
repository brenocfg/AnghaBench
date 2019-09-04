#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filter ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_24__ {int /*<<< orphan*/  NumPendingOidRequests; scalar_t__ Halt; } ;
struct TYPE_23__ {scalar_t__ DeviceExtension; } ;
struct TYPE_22__ {TYPE_1__* FileObject; } ;
struct TYPE_18__ {int /*<<< orphan*/  Status; } ;
struct TYPE_21__ {TYPE_2__ IoStatus; } ;
struct TYPE_20__ {TYPE_9__* Adapter; int /*<<< orphan*/  OpenCloseLock; int /*<<< orphan*/  FileList; scalar_t__ IsBasicDevice; } ;
struct TYPE_19__ {scalar_t__ NumSendingPackets; int /*<<< orphan*/  RecvLock; int /*<<< orphan*/  NetBufferListPool; struct TYPE_19__* Next; struct TYPE_19__* RecvPacketHead; int /*<<< orphan*/  Event; } ;
struct TYPE_17__ {TYPE_3__* FsContext; } ;
typedef  TYPE_3__ SL_PACKET ;
typedef  TYPE_3__ SL_FILE ;
typedef  TYPE_5__ SL_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_6__ IRP ;
typedef  TYPE_7__ IO_STACK_LOCATION ;
typedef  TYPE_8__ DEVICE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* IoGetCurrentIrpStackLocation (TYPE_6__*) ; 
 int /*<<< orphan*/  NdisFreeNetBufferListPool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OID_GEN_CURRENT_PACKET_FILTER ; 
 scalar_t__ SL_LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  SlDelete (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SlFree (TYPE_3__*) ; 
 int /*<<< orphan*/  SlFreeEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFreeLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlSendOidRequest (TYPE_9__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SlSleep (int) ; 
 int /*<<< orphan*/  SlUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlUnlockList (int /*<<< orphan*/ ) ; 

NTSTATUS SlDeviceCloseProc(DEVICE_OBJECT *device_object, IRP *irp)
{
	SL_DEVICE *dev = *((SL_DEVICE **)device_object->DeviceExtension);
	NTSTATUS ret = STATUS_UNSUCCESSFUL;
	IO_STACK_LOCATION *irp_stack = IoGetCurrentIrpStackLocation(irp);

	if (dev->IsBasicDevice)
	{
		// Basic device
		ret = STATUS_SUCCESS;
	}
	else
	{
		// Adapter device
		SL_FILE *f = irp_stack->FileObject->FsContext;

		if (f != NULL)
		{
			bool clear_filter = false;

			// Wait until the number of packet being sent becomes the zero
			while (true)
			{
				if (f->NumSendingPackets == 0)
				{
					break;
				}

				SlSleep(50);
			}

			SlLock(dev->OpenCloseLock);
			{
				// Delete the file from the list
				SlLockList(dev->FileList);
				{
					SlDelete(dev->FileList, f);

					if (SL_LIST_NUM(dev->FileList) == 0)
					{
						// Clear the filter when all files are closed
						clear_filter = true;
					}
				}
				SlUnlockList(dev->FileList);

				if (dev->Adapter->Halt)
				{
					clear_filter = false;
				}

				if (clear_filter)
				{
					InterlockedIncrement(&dev->Adapter->NumPendingOidRequests);
				}
			}
			SlUnlock(dev->OpenCloseLock);

			if (clear_filter)
			{
				// Clear the filter when all files are closed
				UINT filter = 0;
				SlSendOidRequest(dev->Adapter, true, OID_GEN_CURRENT_PACKET_FILTER, &filter, sizeof(filter));
				InterlockedDecrement(&dev->Adapter->NumPendingOidRequests);
			}

			// Release the event
			SlFreeEvent(f->Event);

			// Release the receive queue
			if (true)
			{
				SL_PACKET *p = f->RecvPacketHead;

				while (p != NULL)
				{
					SL_PACKET *p_next = p->Next;

					SlFree(p);

					p = p_next;
				}
			}

			// Release the NET_BUFFER_LIST pool
			NdisFreeNetBufferListPool(f->NetBufferListPool);

			// Release the lock
			SlFreeLock(f->RecvLock);

			SlFree(f);

			ret = STATUS_SUCCESS;
		}
	}

	irp->IoStatus.Status = ret;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return ret;
}