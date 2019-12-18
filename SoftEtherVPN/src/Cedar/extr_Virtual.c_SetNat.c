#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_3__ {void* PublicPort; void* PublicIp; void* DestPort; void* DestIp; void* SrcPort; void* SrcIp; void* Protocol; } ;
typedef  TYPE_1__ NAT_ENTRY ;

/* Variables and functions */

void SetNat(NAT_ENTRY *n, UINT protocol, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, UINT public_ip, UINT public_port)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	n->Protocol = protocol;
	n->SrcIp = src_ip;
	n->SrcPort = src_port;
	n->DestIp = dest_ip;
	n->DestPort = dest_port;
	n->PublicIp = public_ip;
	n->PublicPort = public_port;
}