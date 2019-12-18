#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ CurrentIpQuota; int /*<<< orphan*/  IpCombine; scalar_t__ Now; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  void* UINT ;
typedef  void* UCHAR ;
struct TYPE_8__ {int SrcIsLocalMacAddr; int MacBroadcast; scalar_t__ DataReserved; int /*<<< orphan*/  Data; void* Ttl; void* Protocol; int /*<<< orphan*/  IpParts; scalar_t__ Size; scalar_t__ Expire; int /*<<< orphan*/  Id; void* SrcIP; void* DestIP; } ;
typedef  TYPE_2__ IP_COMBINE ;

/* Variables and functions */
 scalar_t__ IP_COMBINE_INITIAL_BUF_SIZE ; 
 scalar_t__ IP_COMBINE_TIMEOUT ; 
 scalar_t__ IP_COMBINE_WAIT_QUEUE_SIZE_QUOTA ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Malloc (scalar_t__) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IP_COMBINE *InsertIpCombine(VH *v, UINT src_ip, UINT dest_ip, USHORT id, UCHAR protocol, bool mac_broadcast, UCHAR ttl, bool src_is_localmac)
{
	IP_COMBINE *c;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	// Examine the quota
	if ((v->CurrentIpQuota + IP_COMBINE_INITIAL_BUF_SIZE) > IP_COMBINE_WAIT_QUEUE_SIZE_QUOTA)
	{
		// IP packet can not be stored any more
		return NULL;
	}

	c = ZeroMalloc(sizeof(IP_COMBINE));
	c->SrcIsLocalMacAddr = src_is_localmac;
	c->DestIP = dest_ip;
	c->SrcIP = src_ip;
	c->Id = id;
	c->Expire = v->Now + (UINT64)IP_COMBINE_TIMEOUT;
	c->Size = 0;
	c->IpParts = NewList(NULL);
	c->Protocol = protocol;
	c->MacBroadcast = mac_broadcast;
	c->Ttl = ttl;

	// Secure the memory
	c->DataReserved = IP_COMBINE_INITIAL_BUF_SIZE;
	c->Data = Malloc(c->DataReserved);
	v->CurrentIpQuota += c->DataReserved;

	Insert(v->IpCombine, c);

	return c;
}