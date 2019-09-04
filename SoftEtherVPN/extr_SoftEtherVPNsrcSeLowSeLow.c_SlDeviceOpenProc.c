#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  filter ;
typedef  int UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT ;
struct TYPE_31__ {scalar_t__ DeviceExtension; } ;
struct TYPE_30__ {TYPE_1__* FileObject; } ;
struct TYPE_25__ {int /*<<< orphan*/  Status; } ;
struct TYPE_29__ {TYPE_3__ IoStatus; } ;
struct TYPE_24__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Type; } ;
struct TYPE_28__ {int fAllocateNetBuffer; int ContextSize; char PoolTag; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  ProtocolId; TYPE_2__ Header; } ;
struct TYPE_27__ {int Halting; TYPE_13__* Adapter; int /*<<< orphan*/  OpenCloseLock; int /*<<< orphan*/  FileList; scalar_t__ IsBasicDevice; } ;
struct TYPE_26__ {int /*<<< orphan*/  NetBufferListPool; int /*<<< orphan*/  RecvLock; int /*<<< orphan*/  EventNameWin32; int /*<<< orphan*/ * Event; TYPE_1__* FileObject; TYPE_13__* Adapter; TYPE_5__* Device; } ;
struct TYPE_23__ {TYPE_4__* FsContext; } ;
struct TYPE_22__ {int Halt; scalar_t__ NumPendingOidRequests; scalar_t__ Ready; } ;
struct TYPE_21__ {scalar_t__ IntCounter1; } ;
typedef  TYPE_4__ SL_FILE ;
typedef  int /*<<< orphan*/  SL_EVENT ;
typedef  TYPE_5__ SL_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_6__ NET_BUFFER_LIST_POOL_PARAMETERS ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  TYPE_7__ IRP ;
typedef  TYPE_8__ IO_STACK_LOCATION ;
typedef  TYPE_9__ DEVICE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  InterlockedIncrement (scalar_t__*) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* IoGetCurrentIrpStackLocation (TYPE_7__*) ; 
 int /*<<< orphan*/  KeQueryPerformanceCounter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_DEFAULT ; 
 scalar_t__ NDIS_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  NDIS_PROTOCOL_ID_DEFAULT ; 
 int /*<<< orphan*/  NDIS_SIZEOF_NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1 ; 
 int /*<<< orphan*/  NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1 ; 
 int /*<<< orphan*/  NdisAllocateNetBufferListPool (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  OID_GEN_CURRENT_PACKET_FILTER ; 
 char* SL_EVENT_NAME ; 
 int SL_EVENT_NAME_SIZE ; 
 char* SL_EVENT_NAME_WIN32 ; 
 int /*<<< orphan*/  SL_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  SlAdd (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SlFreeEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SlLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SlNewEvent (char*) ; 
 int /*<<< orphan*/  SlNewLock () ; 
 int /*<<< orphan*/  SlSendOidRequest (TYPE_13__*,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  SlSleep (int) ; 
 int /*<<< orphan*/  SlUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlUnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlZero (TYPE_6__*,int) ; 
 TYPE_4__* SlZeroMalloc (int) ; 
 TYPE_10__* sl ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

NTSTATUS SlDeviceOpenProc(DEVICE_OBJECT *device_object, IRP *irp)
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
		bool set_promisc = false;
		volatile UINT *num_pending_oid_requests = NULL;
		UINT64 v;
		char event_name[SL_EVENT_NAME_SIZE];
		char event_name_win32[SL_EVENT_NAME_SIZE];
		SL_EVENT *event_object = NULL;
		LARGE_INTEGER count;
		LARGE_INTEGER freq;

		count = KeQueryPerformanceCounter(&freq);

		InterlockedIncrement(&sl->IntCounter1);

		// Create a new event object
		v = (UINT64)device_object + (UINT64)(++sl->IntCounter1) + *((UINT64 *)(&count));
		sprintf(event_name, SL_EVENT_NAME, (UINT)v, (UINT)(v >> 32) + sl->IntCounter1);
		sprintf(event_name_win32, SL_EVENT_NAME_WIN32, (UINT)v, (UINT)(v >> 32) + sl->IntCounter1);
		event_object = SlNewEvent(event_name);

		SlLock(dev->OpenCloseLock);
		{
			// Add to the opened file list
			SlLockList(dev->FileList);
			{
				if (dev->Halting == false && dev->Adapter != NULL && dev->Adapter->Ready && dev->Adapter->Halt == false)
				{
					// Adapter device
					SL_FILE *f = SlZeroMalloc(sizeof(SL_FILE));
					NET_BUFFER_LIST_POOL_PARAMETERS p;

					f->Device = dev;
					f->Adapter = dev->Adapter;
					f->FileObject = irp_stack->FileObject;

					irp_stack->FileObject->FsContext = f;

					SlAdd(dev->FileList, f);

					ret = STATUS_SUCCESS;
					set_promisc = true;

					// Event
					f->Event = event_object;
					event_object = NULL;
					strcpy(f->EventNameWin32, event_name_win32);

					// Create a lock
					f->RecvLock = SlNewLock();

					// Create a NET_BUFFER_LIST pool
					SlZero(&p, sizeof(p));
					p.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
					p.Header.Revision = NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
					p.Header.Size = NDIS_SIZEOF_NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
					p.ProtocolId = NDIS_PROTOCOL_ID_DEFAULT;
					p.fAllocateNetBuffer = true;
					p.ContextSize = 32 + sizeof(UINT32) * 12;
					p.DataSize = SL_MAX_PACKET_SIZE;
					p.PoolTag = 'SETH';

					f->NetBufferListPool = NdisAllocateNetBufferListPool(NULL, &p);

					num_pending_oid_requests = &dev->Adapter->NumPendingOidRequests;
				}
			}
			SlUnlockList(dev->FileList);
		}
		SlUnlock(dev->OpenCloseLock);

		if (event_object != NULL)
		{
			SlFreeEvent(event_object);
		}

		if (set_promisc)
		{
			// Enable promiscuous mode
			UINT filter = NDIS_PACKET_TYPE_PROMISCUOUS;
			SlSendOidRequest(dev->Adapter, true, OID_GEN_CURRENT_PACKET_FILTER, &filter, sizeof(filter));

			// Wait until the number of OID requests being processed becomes 0
			while ((*num_pending_oid_requests) != 0)
			{
				SlSleep(50);
			}
		}
	}

	irp->IoStatus.Status = ret;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return ret;
}