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
struct t10_vpd {int device_identifier_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int VPD_TMP_BUF_SIZE ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char*) ; 
 int sprintf (unsigned char*,char*,...) ; 
 int strlen (unsigned char*) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,unsigned char*,int) ; 

int transport_dump_vpd_ident_type(
	struct t10_vpd *vpd,
	unsigned char *p_buf,
	int p_buf_len)
{
	unsigned char buf[VPD_TMP_BUF_SIZE];
	int ret = 0;
	int len;

	memset(buf, 0, VPD_TMP_BUF_SIZE);
	len = sprintf(buf, "T10 VPD Identifier Type: ");

	switch (vpd->device_identifier_type) {
	case 0x00:
		sprintf(buf+len, "Vendor specific\n");
		break;
	case 0x01:
		sprintf(buf+len, "T10 Vendor ID based\n");
		break;
	case 0x02:
		sprintf(buf+len, "EUI-64 based\n");
		break;
	case 0x03:
		sprintf(buf+len, "NAA\n");
		break;
	case 0x04:
		sprintf(buf+len, "Relative target port identifier\n");
		break;
	case 0x08:
		sprintf(buf+len, "SCSI name string\n");
		break;
	default:
		sprintf(buf+len, "Unsupported: 0x%02x\n",
				vpd->device_identifier_type);
		ret = -EINVAL;
		break;
	}

	if (p_buf) {
		if (p_buf_len < strlen(buf)+1)
			return -EINVAL;
		strncpy(p_buf, buf, p_buf_len);
	} else {
		pr_debug("%s", buf);
	}

	return ret;
}