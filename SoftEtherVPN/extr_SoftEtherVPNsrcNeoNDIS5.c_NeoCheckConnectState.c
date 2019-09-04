#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ConnectedOld; scalar_t__ Connected; int ConnectedForce; scalar_t__ Halting; int /*<<< orphan*/ * NdisMiniport; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NDIS_STATUS_MEDIA_CONNECT ; 
 int /*<<< orphan*/  NDIS_STATUS_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  NdisMIndicateStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisMIndicateStatusComplete (int /*<<< orphan*/ *) ; 
 TYPE_1__* ctx ; 
 int keep_link ; 

void NeoCheckConnectState()
{
	if (ctx == NULL || ctx->NdisMiniport == NULL)
	{
		return;
	}

	if (keep_link == false)
	{
		if (ctx->ConnectedOld != ctx->Connected || ctx->ConnectedForce)
		{
			ctx->ConnectedForce = FALSE;
			ctx->ConnectedOld = ctx->Connected;
			if (ctx->Halting == FALSE)
			{
				NdisMIndicateStatus(ctx->NdisMiniport,
					ctx->Connected ? NDIS_STATUS_MEDIA_CONNECT : NDIS_STATUS_MEDIA_DISCONNECT,
					0, 0);
				NdisMIndicateStatusComplete(ctx->NdisMiniport);
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
				NdisMIndicateStatus(ctx->NdisMiniport,
					NDIS_STATUS_MEDIA_CONNECT,
					0, 0);
				NdisMIndicateStatusComplete(ctx->NdisMiniport);
			}
		}
	}
}