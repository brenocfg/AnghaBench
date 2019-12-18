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
 unsigned char transport_asciihex_to_binaryhex (unsigned char*) ; 

u32 sas_get_pr_transport_id(
	struct se_portal_group *se_tpg,
	struct se_node_acl *se_nacl,
	struct t10_pr_registration *pr_reg,
	int *format_code,
	unsigned char *buf)
{
	unsigned char binary, *ptr;
	int i;
	u32 off = 4;

	/*
	 * Set PROTOCOL IDENTIFIER to 6h for SAS
	 */
	buf[0] = 0x06;
	/*
	 * From spc4r17, 7.5.4.7 TransportID for initiator ports using SCSI
	 * over SAS Serial SCSI Protocol
	 */
	ptr = &se_nacl->initiatorname[4]; /* Skip over 'naa. prefix */

	for (i = 0; i < 16; i += 2) {
		binary = transport_asciihex_to_binaryhex(&ptr[i]);
		buf[off++] = binary;
	}

	/*
	 * The SAS Transport ID is a hardcoded 24-byte length
	 */
	return 24;
}