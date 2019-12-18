#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  BytesNeeded; int /*<<< orphan*/  InformationBufferLength; int /*<<< orphan*/  InformationBuffer; int /*<<< orphan*/  Oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  BytesNeeded; int /*<<< orphan*/  BytesWritten; int /*<<< orphan*/  InformationBufferLength; int /*<<< orphan*/  InformationBuffer; int /*<<< orphan*/  Oid; } ;
struct TYPE_8__ {TYPE_2__ SET_INFORMATION; TYPE_1__ QUERY_INFORMATION; } ;
struct TYPE_9__ {int RequestType; TYPE_3__ DATA; } ;
typedef  TYPE_4__* PNDIS_OID_REQUEST ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;
typedef  int /*<<< orphan*/  NDIS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_NOT_SUPPORTED ; 
#define  NdisRequestQueryInformation 130 
#define  NdisRequestQueryStatistics 129 
#define  NdisRequestSetInformation 128 
 int /*<<< orphan*/  NeoNdisQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NeoNdisSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NDIS_STATUS NeoNdisOidRequest(NDIS_HANDLE MiniportAdapterContext,
							  PNDIS_OID_REQUEST OidRequest)
{
	NDIS_STATUS ret = STATUS_UNSUCCESSFUL;
	ULONG dummy = 0;

	switch (OidRequest->RequestType)
	{
	case NdisRequestQueryInformation:
	case NdisRequestQueryStatistics:
		ret = NeoNdisQuery(MiniportAdapterContext,
			OidRequest->DATA.QUERY_INFORMATION.Oid,
			OidRequest->DATA.QUERY_INFORMATION.InformationBuffer,
			OidRequest->DATA.QUERY_INFORMATION.InformationBufferLength,
			&OidRequest->DATA.QUERY_INFORMATION.BytesWritten,
			&OidRequest->DATA.QUERY_INFORMATION.BytesNeeded);
		break;

	case NdisRequestSetInformation:
		ret = NeoNdisSet(MiniportAdapterContext,
			OidRequest->DATA.SET_INFORMATION.Oid,
			OidRequest->DATA.SET_INFORMATION.InformationBuffer,
			OidRequest->DATA.SET_INFORMATION.InformationBufferLength,
			&dummy,
			&OidRequest->DATA.SET_INFORMATION.BytesNeeded);
		break;

	default:
		ret = NDIS_STATUS_NOT_SUPPORTED;
		break;
	}

	return ret;
}