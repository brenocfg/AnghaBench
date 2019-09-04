#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int /*<<< orphan*/  PayloadList; } ;
struct TYPE_11__ {scalar_t__ TransformId; } ;
struct TYPE_13__ {scalar_t__ ProtocolId; int /*<<< orphan*/  PayloadList; } ;
struct TYPE_12__ {int /*<<< orphan*/  PayloadList; } ;
struct TYPE_10__ {TYPE_2__ Transform; TYPE_4__ Proposal; TYPE_3__ Sa; } ;
struct TYPE_14__ {TYPE_1__ Payload; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_SA_TRANSFORM_SETTING ;
typedef  TYPE_2__ IKE_PACKET_TRANSFORM_PAYLOAD ;
typedef  TYPE_3__ IKE_PACKET_SA_PAYLOAD ;
typedef  TYPE_4__ IKE_PACKET_PROPOSAL_PAYLOAD ;
typedef  TYPE_5__ IKE_PACKET_PAYLOAD ;
typedef  TYPE_6__ IKE_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IKE_PAYLOAD_PROPOSAL ; 
 int /*<<< orphan*/  IKE_PAYLOAD_SA ; 
 int /*<<< orphan*/  IKE_PAYLOAD_TRANSFORM ; 
 scalar_t__ IKE_PROTOCOL_ID_IKE ; 
 scalar_t__ IKE_TRANSFORM_ID_P1_KEY_IKE ; 
 TYPE_5__* IkeGetPayload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IkeGetPayloadNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransformPayloadToTransformSettingForIkeSa (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

bool GetBestTransformSettingForIkeSa(IKE_SERVER *ike, IKE_PACKET *pr, IKE_SA_TRANSFORM_SETTING *setting)
{
	IKE_PACKET_PAYLOAD *sa_payload;
	IKE_PACKET_SA_PAYLOAD *sa;
	UINT i, num;
	// Validate arguments
	if (ike == NULL || pr == NULL || setting == NULL)
	{
		return false;
	}

	// Get the SA payload
	sa_payload = IkeGetPayload(pr->PayloadList, IKE_PAYLOAD_SA, 0);
	if (sa_payload == NULL)
	{
		return false;
	}

	sa = &sa_payload->Payload.Sa;

	// Scan all proposal payloads
	num = IkeGetPayloadNum(sa->PayloadList, IKE_PAYLOAD_PROPOSAL);
	for (i = 0;i < num;i++)
	{
		IKE_PACKET_PAYLOAD *proposal_payload = IkeGetPayload(sa->PayloadList, IKE_PAYLOAD_PROPOSAL, i);

		if (proposal_payload != NULL)
		{
			IKE_PACKET_PROPOSAL_PAYLOAD *proposal = &proposal_payload->Payload.Proposal;

			// Examine the contents of the proposal payload
			if (proposal->ProtocolId == IKE_PROTOCOL_ID_IKE)
			{
				// Scan all transform payloads
				UINT j, num2;

				num2 = IkeGetPayloadNum(proposal->PayloadList, IKE_PAYLOAD_TRANSFORM);
				for (j = 0;j < num2;j++)
				{
					IKE_PACKET_PAYLOAD *transform_payload = IkeGetPayload(proposal->PayloadList, IKE_PAYLOAD_TRANSFORM, j);
					if (transform_payload != NULL)
					{
						IKE_PACKET_TRANSFORM_PAYLOAD *transform = &transform_payload->Payload.Transform;

						if (transform->TransformId == IKE_TRANSFORM_ID_P1_KEY_IKE)
						{
							IKE_SA_TRANSFORM_SETTING set;

							if (TransformPayloadToTransformSettingForIkeSa(ike, transform, &set))
							{
								Copy(setting, &set, sizeof(IKE_SA_TRANSFORM_SETTING));
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}