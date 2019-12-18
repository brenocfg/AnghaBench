#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_10__ {int Halting; int /*<<< orphan*/  FileList; int /*<<< orphan*/  OpenCloseLock; } ;
struct TYPE_9__ {int /*<<< orphan*/  NumBoundAdapters; } ;
struct TYPE_8__ {int IsClosePending; TYPE_4__* Device; scalar_t__ UnbindContext; } ;
struct TYPE_7__ {int FinalWakeUp; int /*<<< orphan*/  Event; } ;
typedef  TYPE_1__ SL_FILE ;
typedef  TYPE_2__ SL_ADAPTER ;
typedef  scalar_t__ NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisCompleteUnbindAdapterEx (scalar_t__) ; 
 TYPE_1__* SL_LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int SL_LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFreeAdapter (TYPE_2__*) ; 
 int /*<<< orphan*/  SlFreeDevice (TYPE_4__*) ; 
 int /*<<< orphan*/  SlFreeList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlLockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlSet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlSleep (int) ; 
 int /*<<< orphan*/  SlUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlUnlockList (int /*<<< orphan*/ ) ; 
 TYPE_3__* sl ; 

void SlNdisCloseAdapterCompleteExProc(NDIS_HANDLE protocol_binding_context)
{
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;
	NDIS_HANDLE unbind_context = a->UnbindContext;
	bool is_pending = a->IsClosePending;
	UINT j;

	if (is_pending)
	{
		NdisCompleteUnbindAdapterEx(unbind_context);
	}

	for (j = 0;j < 32;j++)
	{
		if (a->Device != NULL)
		{
			a->Device->Halting = true;

			// Wait until the number of file handles that are associated with this device becomes zero
			while (true)
			{
				UINT num_files = 0;

				SlLock(a->Device->OpenCloseLock);
				{
					SlLockList(a->Device->FileList);
					{
						UINT i;
						num_files = SL_LIST_NUM(a->Device->FileList);

						for (i = 0;i < num_files;i++)
						{
							// Hit the associated event
							SL_FILE *f = SL_LIST_DATA(a->Device->FileList, i);

							if (f->FinalWakeUp == false)
							{
								SlSet(f->Event);
								f->FinalWakeUp = true;
							}
						}
					}
					SlUnlockList(a->Device->FileList);
				}
				SlUnlock(a->Device->OpenCloseLock);

				if (num_files == 0)
				{
					break;
				}

				SlSleep(50);
			}
		}
	}

	// Release the device
	if (a->Device != NULL)
	{
		// Delete the file list
		SlFreeList(a->Device->FileList);

		SlFreeDevice(a->Device);
		a->Device = NULL;
	}

	// Release the SL_ADAPTER
	SlFreeAdapter(a);

	if (is_pending)
	{
		InterlockedDecrement(&sl->NumBoundAdapters);
	}
}