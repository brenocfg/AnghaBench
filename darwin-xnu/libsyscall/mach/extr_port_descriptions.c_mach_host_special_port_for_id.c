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
typedef  int /*<<< orphan*/  hsp_ids ;

/* Variables and functions */
#define  HOST_AMFID_PORT 152 
#define  HOST_ATM_NOTIFICATION_PORT 151 
#define  HOST_AUDIT_CONTROL_PORT 150 
#define  HOST_AUTOMOUNTD_PORT 149 
#define  HOST_CLOSURED_PORT 148 
#define  HOST_COALITION_PORT 147 
#define  HOST_CONTAINERD_PORT 146 
#define  HOST_DYNAMIC_PAGER_PORT 145 
#define  HOST_GSSD_PORT 144 
#define  HOST_IO_MASTER_PORT 143 
#define  HOST_KEXTD_PORT 142 
#define  HOST_KTRACE_BACKGROUND_PORT 141 
#define  HOST_LAUNCHCTL_PORT 140 
#define  HOST_LOCKD_PORT 139 
#define  HOST_NODE_PORT 138 
#define  HOST_PORT 137 
#define  HOST_PRIV_PORT 136 
#define  HOST_RESOURCE_NOTIFY_PORT 135 
#define  HOST_SEATBELT_PORT 134 
#define  HOST_SYSDIAGNOSE_PORT 133 
#define  HOST_SYSPOLICYD_PORT 132 
#define  HOST_TELEMETRY_PORT 131 
#define  HOST_UNFREED_PORT 130 
#define  HOST_USER_NOTIFICATION_PORT 129 
#define  HOST_XPC_EXCEPTION_PORT 128 
 char const* SP_ENTRY (int /*<<< orphan*/ ) ; 
 int port_for_id_internal (char const*,char const**,int) ; 

int
mach_host_special_port_for_id(const char *id)
{
	static const char *hsp_ids[] = {
#define SP_ENTRY(id) [id] = #id
		SP_ENTRY(HOST_PORT),
		SP_ENTRY(HOST_PRIV_PORT),
		SP_ENTRY(HOST_IO_MASTER_PORT),
		SP_ENTRY(HOST_DYNAMIC_PAGER_PORT),
		SP_ENTRY(HOST_AUDIT_CONTROL_PORT),
		SP_ENTRY(HOST_USER_NOTIFICATION_PORT),
		SP_ENTRY(HOST_AUTOMOUNTD_PORT),
		SP_ENTRY(HOST_LOCKD_PORT),
		SP_ENTRY(HOST_KTRACE_BACKGROUND_PORT),
		SP_ENTRY(HOST_SEATBELT_PORT),
		SP_ENTRY(HOST_KEXTD_PORT),
		SP_ENTRY(HOST_LAUNCHCTL_PORT),
		SP_ENTRY(HOST_UNFREED_PORT),
		SP_ENTRY(HOST_AMFID_PORT),
		SP_ENTRY(HOST_GSSD_PORT),
		SP_ENTRY(HOST_TELEMETRY_PORT),
		SP_ENTRY(HOST_ATM_NOTIFICATION_PORT),
		SP_ENTRY(HOST_COALITION_PORT),
		SP_ENTRY(HOST_SYSDIAGNOSE_PORT),
		SP_ENTRY(HOST_XPC_EXCEPTION_PORT),
		SP_ENTRY(HOST_CONTAINERD_PORT),
		SP_ENTRY(HOST_NODE_PORT),
		SP_ENTRY(HOST_RESOURCE_NOTIFY_PORT),
		SP_ENTRY(HOST_CLOSURED_PORT),
		SP_ENTRY(HOST_SYSPOLICYD_PORT),
	};

	return port_for_id_internal(id, hsp_ids,
			sizeof(hsp_ids) / sizeof(hsp_ids[0]));
}