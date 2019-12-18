#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_23__ {scalar_t__ choice; int /*<<< orphan*/  localAreaAddress; } ;
struct TYPE_18__ {scalar_t__ choice; } ;
struct TYPE_19__ {scalar_t__ choice; TYPE_4__ t120; } ;
struct TYPE_20__ {TYPE_5__ application; } ;
struct TYPE_21__ {scalar_t__ choice; TYPE_6__ data; } ;
struct TYPE_15__ {scalar_t__ choice; int /*<<< orphan*/  h2250LogicalChannelParameters; } ;
struct TYPE_22__ {TYPE_7__ dataType; TYPE_1__ multiplexParameters; } ;
struct TYPE_16__ {scalar_t__ choice; int /*<<< orphan*/  h2250LogicalChannelParameters; } ;
struct TYPE_17__ {int options; TYPE_2__ multiplexParameters; } ;
struct TYPE_13__ {TYPE_9__ networkAddress; } ;
struct TYPE_14__ {int options; TYPE_10__ separateStack; TYPE_8__ forwardLogicalChannelParameters; TYPE_3__ reverseLogicalChannelParameters; } ;
typedef  TYPE_11__ OpenLogicalChannel ;

/* Variables and functions */
 scalar_t__ eDataApplicationCapability_application_t120 ; 
 scalar_t__ eDataProtocolCapability_separateLANStack ; 
 scalar_t__ eDataType_data ; 
 scalar_t__ eNetworkAccessParameters_networkAddress_localAreaAddress ; 
 scalar_t__ eOpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters ; 
 int eOpenLogicalChannel_reverseLogicalChannelParameters ; 
 int eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters ; 
 scalar_t__ eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters ; 
 int eOpenLogicalChannel_separateStack ; 
 int expect_t120 (struct sk_buff*,struct nf_conn*,int,unsigned char**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int process_h245_channel (struct sk_buff*,struct nf_conn*,int,unsigned char**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_olc(struct sk_buff *skb, struct nf_conn *ct,
		       enum ip_conntrack_info ctinfo,
		       unsigned char **data, int dataoff,
		       OpenLogicalChannel *olc)
{
	int ret;

	pr_debug("nf_ct_h323: OpenLogicalChannel\n");

	if (olc->forwardLogicalChannelParameters.multiplexParameters.choice ==
	    eOpenLogicalChannel_forwardLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters)
	{
		ret = process_h245_channel(skb, ct, ctinfo, data, dataoff,
					   &olc->
					   forwardLogicalChannelParameters.
					   multiplexParameters.
					   h2250LogicalChannelParameters);
		if (ret < 0)
			return -1;
	}

	if ((olc->options &
	     eOpenLogicalChannel_reverseLogicalChannelParameters) &&
	    (olc->reverseLogicalChannelParameters.options &
	     eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters)
	    && (olc->reverseLogicalChannelParameters.multiplexParameters.
		choice ==
		eOpenLogicalChannel_reverseLogicalChannelParameters_multiplexParameters_h2250LogicalChannelParameters))
	{
		ret =
		    process_h245_channel(skb, ct, ctinfo, data, dataoff,
					 &olc->
					 reverseLogicalChannelParameters.
					 multiplexParameters.
					 h2250LogicalChannelParameters);
		if (ret < 0)
			return -1;
	}

	if ((olc->options & eOpenLogicalChannel_separateStack) &&
	    olc->forwardLogicalChannelParameters.dataType.choice ==
	    eDataType_data &&
	    olc->forwardLogicalChannelParameters.dataType.data.application.
	    choice == eDataApplicationCapability_application_t120 &&
	    olc->forwardLogicalChannelParameters.dataType.data.application.
	    t120.choice == eDataProtocolCapability_separateLANStack &&
	    olc->separateStack.networkAddress.choice ==
	    eNetworkAccessParameters_networkAddress_localAreaAddress) {
		ret = expect_t120(skb, ct, ctinfo, data, dataoff,
				  &olc->separateStack.networkAddress.
				  localAreaAddress);
		if (ret < 0)
			return -1;
	}

	return 0;
}