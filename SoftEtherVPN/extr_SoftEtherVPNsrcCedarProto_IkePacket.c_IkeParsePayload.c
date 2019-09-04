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
typedef  int UINT ;
struct TYPE_6__ {int /*<<< orphan*/  GeneralData; int /*<<< orphan*/  NatOa; int /*<<< orphan*/  Delete; int /*<<< orphan*/  Notice; int /*<<< orphan*/  CertRequest; int /*<<< orphan*/  Cert; int /*<<< orphan*/  Id; int /*<<< orphan*/  Transform; int /*<<< orphan*/  Proposal; int /*<<< orphan*/  Sa; } ;
struct TYPE_7__ {int PayloadType; int /*<<< orphan*/  BitArray; TYPE_1__ Payload; } ;
typedef  TYPE_2__ IKE_PACKET_PAYLOAD ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CloneBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
#define  IKE_PAYLOAD_CERT 145 
#define  IKE_PAYLOAD_CERT_REQUEST 144 
#define  IKE_PAYLOAD_DELETE 143 
#define  IKE_PAYLOAD_HASH 142 
#define  IKE_PAYLOAD_ID 141 
#define  IKE_PAYLOAD_KEY_EXCHANGE 140 
#define  IKE_PAYLOAD_NAT_D 139 
#define  IKE_PAYLOAD_NAT_D_DRAFT 138 
#define  IKE_PAYLOAD_NAT_OA 137 
#define  IKE_PAYLOAD_NAT_OA_DRAFT 136 
#define  IKE_PAYLOAD_NAT_OA_DRAFT_2 135 
#define  IKE_PAYLOAD_NOTICE 134 
#define  IKE_PAYLOAD_PROPOSAL 133 
#define  IKE_PAYLOAD_RAND 132 
#define  IKE_PAYLOAD_SA 131 
#define  IKE_PAYLOAD_SIGN 130 
#define  IKE_PAYLOAD_TRANSFORM 129 
#define  IKE_PAYLOAD_VENDOR_ID 128 
 int IkeParseCertPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseCertRequestPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseDataPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseDeletePayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseIdPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseNatOaPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseNoticePayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseProposalPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseSaPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IkeParseTransformPayload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IKE_PACKET_PAYLOAD *IkeParsePayload(UINT payload_type, BUF *b)
{
	IKE_PACKET_PAYLOAD *p = NULL;
	bool ok = true;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	p = ZeroMalloc(sizeof(IKE_PACKET_PAYLOAD));
	p->PayloadType = payload_type;

	switch (p->PayloadType)
	{
	case IKE_PAYLOAD_SA:					// SA payload
		ok = IkeParseSaPayload(&p->Payload.Sa, b);
		break;

	case IKE_PAYLOAD_PROPOSAL:			// Proposal payload
		ok = IkeParseProposalPayload(&p->Payload.Proposal, b);
		break;

	case IKE_PAYLOAD_TRANSFORM:			// Proposal payload
		ok = IkeParseTransformPayload(&p->Payload.Transform, b);
		break;

	case IKE_PAYLOAD_ID:					// ID payload
		ok = IkeParseIdPayload(&p->Payload.Id, b);
		break;

	case IKE_PAYLOAD_CERT:				// Certificate payload
		ok = IkeParseCertPayload(&p->Payload.Cert, b);
		break;

	case IKE_PAYLOAD_CERT_REQUEST:		// Certificate request payload
		ok = IkeParseCertRequestPayload(&p->Payload.CertRequest, b);
		break;

	case IKE_PAYLOAD_NOTICE:				// Notification Payload
		ok = IkeParseNoticePayload(&p->Payload.Notice, b);
		break;

	case IKE_PAYLOAD_DELETE:				// Deletion payload
		ok = IkeParseDeletePayload(&p->Payload.Delete, b);
		break;

	case IKE_PAYLOAD_NAT_OA:
	case IKE_PAYLOAD_NAT_OA_DRAFT:
	case IKE_PAYLOAD_NAT_OA_DRAFT_2:
		ok = IkeParseNatOaPayload(&p->Payload.NatOa, b);
		break;

	case IKE_PAYLOAD_KEY_EXCHANGE:		// Key exchange payload
	case IKE_PAYLOAD_HASH:				// Hash payload
	case IKE_PAYLOAD_SIGN:				// Signature payload
	case IKE_PAYLOAD_RAND:				// Random number payload
	case IKE_PAYLOAD_VENDOR_ID:			// Vendor ID payload
	case IKE_PAYLOAD_NAT_D:				// NAT-D payload
	case IKE_PAYLOAD_NAT_D_DRAFT:		// NAT-D payload (draft)
	default:
		ok = IkeParseDataPayload(&p->Payload.GeneralData, b);
		break;
	}

	if (ok == false)
	{
		Free(p);
		p = NULL;
	}
	else
	{
		p->BitArray = CloneBuf(b);
	}

	return p;
}