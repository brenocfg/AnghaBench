#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  PayloadSize; } ;
struct TYPE_17__ {TYPE_10__* ICMPHeader; } ;
struct TYPE_16__ {TYPE_4__* IPv6Header; } ;
struct TYPE_13__ {TYPE_1__* RouterAdvertisementHeader; } ;
struct TYPE_14__ {scalar_t__ Type; TYPE_2__ Headers; } ;
struct TYPE_19__ {scalar_t__ TypeL3; scalar_t__ TypeL4; TYPE_7__ IPv6HeaderPacketInfo; TYPE_6__ L4; TYPE_5__ L3; TYPE_3__ ICMPv6HeaderPacketInfo; } ;
struct TYPE_15__ {int /*<<< orphan*/  DestAddress; int /*<<< orphan*/  SrcAddress; } ;
struct TYPE_12__ {scalar_t__ Lifetime; } ;
struct TYPE_11__ {scalar_t__ Checksum; } ;
typedef  TYPE_8__ PKT ;

/* Variables and functions */
 scalar_t__ CalcChecksumForIPv6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ICMPV6_TYPE_ROUTER_ADVERTISEMENT ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV6 ; 
 scalar_t__ L3_IPV6 ; 
 scalar_t__ L4_ICMPV6 ; 

bool DeleteIPv6DefaultRouterInRA(PKT *p)
{
	if (p->TypeL3 == L3_IPV6 && p->TypeL4 == L4_ICMPV6 &&
		(p->ICMPv6HeaderPacketInfo.Type == ICMPV6_TYPE_ROUTER_ADVERTISEMENT))
	{
		if (p->ICMPv6HeaderPacketInfo.Headers.RouterAdvertisementHeader->Lifetime != 0)
		{
			p->ICMPv6HeaderPacketInfo.Headers.RouterAdvertisementHeader->Lifetime = 0;

			p->L4.ICMPHeader->Checksum = 0;
			p->L4.ICMPHeader->Checksum =
				CalcChecksumForIPv6(&p->L3.IPv6Header->SrcAddress,
					&p->L3.IPv6Header->DestAddress, IP_PROTO_ICMPV6,
					p->L4.ICMPHeader, p->IPv6HeaderPacketInfo.PayloadSize, 0);
		}
	}

	return false;
}