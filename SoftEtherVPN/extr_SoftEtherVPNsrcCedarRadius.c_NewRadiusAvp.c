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
typedef  int UINT ;
typedef  void* UCHAR ;
struct TYPE_4__ {int VendorId; int /*<<< orphan*/  Data; void* DataSize; void* VendorCode; void* Type; } ;
typedef  TYPE_1__ RADIUS_AVP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  Debug (char*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

RADIUS_AVP *NewRadiusAvp(UCHAR type, UINT vendor_id, UCHAR vendor_code, void *data, UINT size)
{
	RADIUS_AVP *p = ZeroMalloc(sizeof(RADIUS_AVP));

	p->Type = type;
	p->VendorId = vendor_id;
	p->VendorCode = vendor_code;
	p->DataSize = (UCHAR)size;
	Copy(p->Data, data, (UCHAR)size);

	if (size >= 256)
	{
		Debug("!! size = %u\n", size);
	}

	return p;
}