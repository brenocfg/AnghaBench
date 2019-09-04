#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  GeneralData; int /*<<< orphan*/  Delete; int /*<<< orphan*/  Notice; int /*<<< orphan*/  CertRequest; int /*<<< orphan*/  Cert; int /*<<< orphan*/  Id; int /*<<< orphan*/  Transform; int /*<<< orphan*/  Proposal; int /*<<< orphan*/  Sa; } ;
struct TYPE_6__ {int PayloadType; int /*<<< orphan*/ * BitArray; TYPE_1__ Payload; } ;
typedef  TYPE_2__ IKE_PACKET_PAYLOAD ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  IkeFreeCertPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeCertRequestPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeDataPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeDeletePayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeIdPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeNoticePayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeProposalPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeSaPayload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IkeFreeTransformPayload (int /*<<< orphan*/ *) ; 

void IkeFreePayload(IKE_PACKET_PAYLOAD *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	switch (p->PayloadType)
	{
	case IKE_PAYLOAD_SA:					// SA payload
		IkeFreeSaPayload(&p->Payload.Sa);
		break;

	case IKE_PAYLOAD_PROPOSAL:			// Proposal payload
		IkeFreeProposalPayload(&p->Payload.Proposal);
		break;

	case IKE_PAYLOAD_TRANSFORM:			// Proposal payload
		IkeFreeTransformPayload(&p->Payload.Transform);
		break;

	case IKE_PAYLOAD_ID:					// ID payload
		IkeFreeIdPayload(&p->Payload.Id);
		break;

	case IKE_PAYLOAD_CERT:				// Certificate payload
		IkeFreeCertPayload(&p->Payload.Cert);
		break;

	case IKE_PAYLOAD_CERT_REQUEST:		// Certificate request payload
		IkeFreeCertRequestPayload(&p->Payload.CertRequest);
		break;

	case IKE_PAYLOAD_NOTICE:				// Notification Payload
		IkeFreeNoticePayload(&p->Payload.Notice);
		break;

	case IKE_PAYLOAD_DELETE:				// Deletion payload
		IkeFreeDeletePayload(&p->Payload.Delete);
		break;

	case IKE_PAYLOAD_NAT_OA:				// NAT-OD payload
	case IKE_PAYLOAD_NAT_OA_DRAFT:
	case IKE_PAYLOAD_NAT_OA_DRAFT_2:
		// Do Nothing
		break;

	case IKE_PAYLOAD_KEY_EXCHANGE:		// Key exchange payload
	case IKE_PAYLOAD_HASH:				// Hash payload
	case IKE_PAYLOAD_SIGN:				// Signature payload
	case IKE_PAYLOAD_RAND:				// Random number payload
	case IKE_PAYLOAD_VENDOR_ID:			// Vendor ID payload
	case IKE_PAYLOAD_NAT_D:				// NAT-D payload
	case IKE_PAYLOAD_NAT_D_DRAFT:		// NAT-D payload (draft)
	default:
		IkeFreeDataPayload(&p->Payload.GeneralData);
		break;
	}

	if (p->BitArray != NULL)
	{
		FreeBuf(p->BitArray);
	}

	Free(p);
}