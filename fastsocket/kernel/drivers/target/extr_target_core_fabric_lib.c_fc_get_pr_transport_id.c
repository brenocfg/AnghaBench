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
struct t10_pr_registration {int dummy; } ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {unsigned char* initiatorname; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (unsigned char*,char*,int) ; 
 unsigned char transport_asciihex_to_binaryhex (unsigned char*) ; 

u32 fc_get_pr_transport_id(
	struct se_portal_group *se_tpg,
	struct se_node_acl *se_nacl,
	struct t10_pr_registration *pr_reg,
	int *format_code,
	unsigned char *buf)
{
	unsigned char binary, *ptr;
	int i;
	u32 off = 8;

	/*
	 * PROTOCOL IDENTIFIER is 0h for FCP-2
	 *
	 * From spc4r17, 7.5.4.2 TransportID for initiator ports using
	 * SCSI over Fibre Channel
	 *
	 * We convert the ASCII formatted N Port name into a binary
	 * encoded TransportID.
	 */
	ptr = &se_nacl->initiatorname[0];

	for (i = 0; i < 24; ) {
		if (!strncmp(&ptr[i], ":", 1)) {
			i++;
			continue;
		}
		binary = transport_asciihex_to_binaryhex(&ptr[i]);
		buf[off++] = binary;
		i += 2;
	}
	/*
	 * The FC Transport ID is a hardcoded 24-byte length
	 */
	return 24;
}