#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* Mtu; void* Prefix; void* TargetLinkLayer; void* SourceLinkLayer; } ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_PREFIX ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_MTU ;
typedef  TYPE_1__ ICMPV6_OPTION_LIST ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_LINK_LAYER ;

/* Variables and functions */
 void* Clone (void*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void CloneICMPv6Options(ICMPV6_OPTION_LIST *dst, ICMPV6_OPTION_LIST *src)
{
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	Zero(dst, sizeof(ICMPV6_OPTION_LIST));

	dst->SourceLinkLayer = Clone(src->SourceLinkLayer, sizeof(ICMPV6_OPTION_LINK_LAYER));
	dst->TargetLinkLayer = Clone(src->TargetLinkLayer, sizeof(ICMPV6_OPTION_LINK_LAYER));
	dst->Prefix = Clone(src->Prefix, sizeof(ICMPV6_OPTION_PREFIX));
	dst->Mtu = Clone(src->Mtu, sizeof(ICMPV6_OPTION_MTU));
}