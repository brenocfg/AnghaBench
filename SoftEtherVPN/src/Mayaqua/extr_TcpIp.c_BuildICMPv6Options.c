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
struct TYPE_3__ {int /*<<< orphan*/ * Mtu; int /*<<< orphan*/ * Prefix; int /*<<< orphan*/ * TargetLinkLayer; int /*<<< orphan*/ * SourceLinkLayer; } ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_PREFIX ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_MTU ;
typedef  TYPE_1__ ICMPV6_OPTION_LIST ;
typedef  int /*<<< orphan*/  ICMPV6_OPTION_LINK_LAYER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BuildICMPv6OptionValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICMPV6_OPTION_TYPE_MTU ; 
 int /*<<< orphan*/  ICMPV6_OPTION_TYPE_PREFIX ; 
 int /*<<< orphan*/  ICMPV6_OPTION_TYPE_SOURCE_LINK_LAYER ; 
 int /*<<< orphan*/  ICMPV6_OPTION_TYPE_TARGET_LINK_LAYER ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BUF *BuildICMPv6Options(ICMPV6_OPTION_LIST *o)
{
	BUF *b;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	b = NewBuf();

	if (o->SourceLinkLayer != NULL)
	{
		BuildICMPv6OptionValue(b, ICMPV6_OPTION_TYPE_SOURCE_LINK_LAYER, o->SourceLinkLayer, sizeof(ICMPV6_OPTION_LINK_LAYER));
	}
	if (o->TargetLinkLayer != NULL)
	{
		BuildICMPv6OptionValue(b, ICMPV6_OPTION_TYPE_TARGET_LINK_LAYER, o->TargetLinkLayer, sizeof(ICMPV6_OPTION_LINK_LAYER));
	}
	if (o->Prefix != NULL)
	{
		BuildICMPv6OptionValue(b, ICMPV6_OPTION_TYPE_PREFIX, o->Prefix, sizeof(ICMPV6_OPTION_PREFIX));
	}
	if (o->Mtu != NULL)
	{
		BuildICMPv6OptionValue(b, ICMPV6_OPTION_TYPE_MTU, o->Mtu, sizeof(ICMPV6_OPTION_MTU));
	}

	SeekBuf(b, 0, 0);

	return b;
}