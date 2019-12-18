#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_5__ {int choice; int /*<<< orphan*/  openLogicalChannelAck; } ;
struct TYPE_6__ {int choice; int /*<<< orphan*/  openLogicalChannel; } ;
struct TYPE_7__ {int choice; TYPE_1__ response; TYPE_2__ request; } ;
typedef  TYPE_3__ MultimediaSystemControlMessage ;

/* Variables and functions */
#define  eMultimediaSystemControlMessage_request 129 
#define  eMultimediaSystemControlMessage_response 128 
 int eRequestMessage_openLogicalChannel ; 
 int eResponseMessage_openLogicalChannelAck ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int process_olc (struct sk_buff*,struct nf_conn*,int,unsigned char**,int,int /*<<< orphan*/ *) ; 
 int process_olca (struct sk_buff*,struct nf_conn*,int,unsigned char**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_h245(struct sk_buff *skb, struct nf_conn *ct,
			enum ip_conntrack_info ctinfo,
			unsigned char **data, int dataoff,
			MultimediaSystemControlMessage *mscm)
{
	switch (mscm->choice) {
	case eMultimediaSystemControlMessage_request:
		if (mscm->request.choice ==
		    eRequestMessage_openLogicalChannel) {
			return process_olc(skb, ct, ctinfo, data, dataoff,
					   &mscm->request.openLogicalChannel);
		}
		pr_debug("nf_ct_h323: H.245 Request %d\n",
			 mscm->request.choice);
		break;
	case eMultimediaSystemControlMessage_response:
		if (mscm->response.choice ==
		    eResponseMessage_openLogicalChannelAck) {
			return process_olca(skb, ct, ctinfo, data, dataoff,
					    &mscm->response.
					    openLogicalChannelAck);
		}
		pr_debug("nf_ct_h323: H.245 Response %d\n",
			 mscm->response.choice);
		break;
	default:
		pr_debug("nf_ct_h323: H.245 signal %d\n", mscm->choice);
		break;
	}

	return 0;
}