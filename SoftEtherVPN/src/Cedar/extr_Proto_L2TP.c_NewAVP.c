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
typedef  void* USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int Mandatory; scalar_t__ DataSize; int /*<<< orphan*/  Data; void* VendorID; void* Type; } ;
typedef  TYPE_1__ L2TP_AVP ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (void*,scalar_t__) ; 
 TYPE_1__* ZeroMalloc (int) ; 

L2TP_AVP *NewAVP(USHORT type, bool mandatory, USHORT vendor_id, void *data, UINT data_size)
{
	L2TP_AVP *a;
	// Validate arguments
	if (data_size != 0 && data == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(L2TP_AVP));

	a->Type = type;
	a->Mandatory = mandatory;
	a->VendorID = vendor_id;
	a->Data = Clone(data, data_size);
	a->DataSize = data_size;

	return a;
}