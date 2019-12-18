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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MXM_MXDS_ADAPTER_0 ; 
 int /*<<< orphan*/  MXM_MXDS_ADAPTER_IGD ; 
 int /*<<< orphan*/  NOUVEAU_DSM_LED ; 
 int NOUVEAU_DSM_LED_STAMINA ; 
 int /*<<< orphan*/  mxm_wmi_call_mxds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_wmi_call_mxmx (int /*<<< orphan*/ ) ; 
 int nouveau_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nouveau_dsm_switch_mux(acpi_handle handle, int mux_id)
{
	mxm_wmi_call_mxmx(mux_id == NOUVEAU_DSM_LED_STAMINA ? MXM_MXDS_ADAPTER_IGD : MXM_MXDS_ADAPTER_0);
	mxm_wmi_call_mxds(mux_id == NOUVEAU_DSM_LED_STAMINA ? MXM_MXDS_ADAPTER_IGD : MXM_MXDS_ADAPTER_0);
	return nouveau_dsm(handle, NOUVEAU_DSM_LED, mux_id, NULL);
}