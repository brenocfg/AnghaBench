#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  IpWaitTable; scalar_t__ Now; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ Expire; scalar_t__ DestIP; scalar_t__ SrcIP; scalar_t__ Size; void* Data; } ;
typedef  TYPE_2__ IP_WAIT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IP_WAIT_FOR_ARP_TIMEOUT ; 
 TYPE_2__* ZeroMalloc (int) ; 

void InsertIpWaitTable(VH *v, UINT dest_ip, UINT src_ip, void *data, UINT size)
{
	IP_WAIT *w;
	// Validate arguments
	if (v == NULL || data == NULL || size == 0)
	{
		return;
	}

	w = ZeroMalloc(sizeof(IP_WAIT));
	w->Data = data;
	w->Size = size;
	w->SrcIP = src_ip;
	w->DestIP = dest_ip;
	w->Expire = v->Now + (UINT64)IP_WAIT_FOR_ARP_TIMEOUT;

	Add(v->IpWaitTable, w);
}