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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_9__ {scalar_t__ ConnectedOld; scalar_t__ Connected; int ConnectedForce; scalar_t__ Halting; int /*<<< orphan*/ * NdisMiniport; } ;
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Revision; int /*<<< orphan*/  Type; } ;
struct TYPE_8__ {int StatusBufferSize; void* MediaConnectState; struct TYPE_8__* StatusBuffer; int /*<<< orphan*/  StatusCode; int /*<<< orphan*/  PauseFunctions; int /*<<< orphan*/  RcvLinkSpeed; int /*<<< orphan*/  XmitLinkSpeed; int /*<<< orphan*/  MediaDuplexState; TYPE_1__ Header; int /*<<< orphan*/ * SourceHandle; } ;
typedef  TYPE_2__ NDIS_STATUS_INDICATION ;
typedef  TYPE_2__ NDIS_LINK_STATE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 void* MediaConnectStateConnected ; 
 void* MediaConnectStateDisconnected ; 
 int /*<<< orphan*/  NDIS_LINK_STATE_REVISION_1 ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_DEFAULT ; 
 int /*<<< orphan*/  NDIS_OBJECT_TYPE_STATUS_INDICATION ; 
 int /*<<< orphan*/  NDIS_SIZEOF_LINK_STATE_REVISION_1 ; 
 int /*<<< orphan*/  NDIS_SIZEOF_STATUS_INDICATION_REVISION_1 ; 
 int /*<<< orphan*/  NDIS_STATUS_INDICATION_REVISION_1 ; 
 int /*<<< orphan*/  NDIS_STATUS_LINK_STATE ; 
 int /*<<< orphan*/  NdisMIndicateStatusEx (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  NdisPauseFunctionsSendAndReceive ; 
 int /*<<< orphan*/  NdisPauseFunctionsUnsupported ; 
 int /*<<< orphan*/  NeoZero (TYPE_2__*,int) ; 
 TYPE_4__* ctx ; 
 int keep_link ; 
 int /*<<< orphan*/  max_speed ; 

void NeoCheckConnectState()
{
	NDIS_STATUS_INDICATION t;
	NDIS_LINK_STATE state;
	if (ctx == NULL || ctx->NdisMiniport == NULL)
	{
		return;
	}

	NeoZero(&t, sizeof(t));
	t.Header.Type = NDIS_OBJECT_TYPE_STATUS_INDICATION;
	t.Header.Revision = NDIS_STATUS_INDICATION_REVISION_1;
	t.Header.Size = NDIS_SIZEOF_STATUS_INDICATION_REVISION_1;

	t.SourceHandle = ctx->NdisMiniport;

	NeoZero(&state, sizeof(state));
	state.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
	state.Header.Revision = NDIS_LINK_STATE_REVISION_1;
	state.Header.Size = NDIS_SIZEOF_LINK_STATE_REVISION_1;

	state.MediaDuplexState = NdisPauseFunctionsSendAndReceive;
	state.XmitLinkSpeed = state.RcvLinkSpeed = max_speed;
	state.PauseFunctions = NdisPauseFunctionsUnsupported;

	t.StatusCode = NDIS_STATUS_LINK_STATE;
	t.StatusBuffer = &state;
	t.StatusBufferSize = sizeof(NDIS_LINK_STATE);

	if (keep_link == false)
	{
		if (ctx->ConnectedOld != ctx->Connected || ctx->ConnectedForce)
		{
			ctx->ConnectedForce = FALSE;
			ctx->ConnectedOld = ctx->Connected;
			if (ctx->Halting == FALSE)
			{
				state.MediaConnectState = ctx->Connected ? MediaConnectStateConnected : MediaConnectStateDisconnected;
				NdisMIndicateStatusEx(ctx->NdisMiniport, &t);
			}
		}
	}
	else
	{
		if (ctx->ConnectedForce)
		{
			ctx->ConnectedForce = false;

			if (ctx->Halting == FALSE)
			{
				state.MediaConnectState = MediaConnectStateConnected;
				NdisMIndicateStatusEx(ctx->NdisMiniport, &t);
			}
		}
	}
}