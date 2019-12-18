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
typedef  void* UINT ;
struct TYPE_4__ {int /*<<< orphan*/  HashCodeForRecv; int /*<<< orphan*/  HashCodeForSend; void* PublicPort; void* PublicIp; void* DestPort; void* DestIp; void* SrcPort; void* SrcIp; void* Protocol; } ;
typedef  TYPE_1__ NATIVE_NAT_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void NnSetNat(NATIVE_NAT_ENTRY *e, UINT protocol, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, UINT pub_ip, UINT pub_port)
{
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	Zero(e, sizeof(NATIVE_NAT_ENTRY));

	e->Protocol = protocol;
	e->SrcIp = src_ip;
	e->SrcPort = src_port;
	e->DestIp = dest_ip;
	e->DestPort = dest_port;
	e->PublicIp = pub_ip;
	e->PublicPort = pub_port;
	e->HashCodeForSend = e->HashCodeForRecv = INFINITE;
}