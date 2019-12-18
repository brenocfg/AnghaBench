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
typedef  int u32 ;
struct se_portal_group {int dummy; } ;

/* Variables and functions */

char *sas_parse_pr_out_transport_id(
	struct se_portal_group *se_tpg,
	const char *buf,
	u32 *out_tid_len,
	char **port_nexus_ptr)
{
	/*
	 * Assume the FORMAT CODE 00b from spc4r17, 7.5.4.7 TransportID
	 * for initiator ports using SCSI over SAS Serial SCSI Protocol
	 *
	 * The TransportID for a SAS Initiator Port is of fixed size of
	 * 24 bytes, and SAS does not contain a I_T nexus identifier,
	 * so we return the **port_nexus_ptr set to NULL.
	 */
	*port_nexus_ptr = NULL;
	*out_tid_len = 24;

	return (char *)&buf[4];
}