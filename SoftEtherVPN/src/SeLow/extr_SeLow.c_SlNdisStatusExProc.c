#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SL_ADAPTER ;
typedef  int /*<<< orphan*/  NDIS_STATUS_INDICATION ;
typedef  scalar_t__ NDIS_HANDLE ;

/* Variables and functions */

void SlNdisStatusExProc(NDIS_HANDLE protocol_binding_context, NDIS_STATUS_INDICATION *status_indication)
{
	SL_ADAPTER *a = (SL_ADAPTER *)protocol_binding_context;
}