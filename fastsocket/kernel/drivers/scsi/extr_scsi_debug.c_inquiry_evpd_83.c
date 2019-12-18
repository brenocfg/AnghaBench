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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 char* inq_product_id ; 
 char* inq_vendor_id ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int inquiry_evpd_83(unsigned char * arr, int port_group_id,
			   int target_dev_id, int dev_id_num,
			   const char * dev_id_str,
			   int dev_id_str_len)
{
	int num, port_a;
	char b[32];

	port_a = target_dev_id + 1;
	/* T10 vendor identifier field format (faked) */
	arr[0] = 0x2;	/* ASCII */
	arr[1] = 0x1;
	arr[2] = 0x0;
	memcpy(&arr[4], inq_vendor_id, 8);
	memcpy(&arr[12], inq_product_id, 16);
	memcpy(&arr[28], dev_id_str, dev_id_str_len);
	num = 8 + 16 + dev_id_str_len;
	arr[3] = num;
	num += 4;
	if (dev_id_num >= 0) {
		/* NAA-5, Logical unit identifier (binary) */
		arr[num++] = 0x1;	/* binary (not necessarily sas) */
		arr[num++] = 0x3;	/* PIV=0, lu, naa */
		arr[num++] = 0x0;
		arr[num++] = 0x8;
		arr[num++] = 0x53;  /* naa-5 ieee company id=0x333333 (fake) */
		arr[num++] = 0x33;
		arr[num++] = 0x33;
		arr[num++] = 0x30;
		arr[num++] = (dev_id_num >> 24);
		arr[num++] = (dev_id_num >> 16) & 0xff;
		arr[num++] = (dev_id_num >> 8) & 0xff;
		arr[num++] = dev_id_num & 0xff;
		/* Target relative port number */
		arr[num++] = 0x61;	/* proto=sas, binary */
		arr[num++] = 0x94;	/* PIV=1, target port, rel port */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x4;	/* length */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x0;	/* reserved */
		arr[num++] = 0x0;
		arr[num++] = 0x1;	/* relative port A */
	}
	/* NAA-5, Target port identifier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* piv=1, target port, naa */
	arr[num++] = 0x0;
	arr[num++] = 0x8;
	arr[num++] = 0x52;	/* naa-5, company id=0x222222 (fake) */
	arr[num++] = 0x22;
	arr[num++] = 0x22;
	arr[num++] = 0x20;
	arr[num++] = (port_a >> 24);
	arr[num++] = (port_a >> 16) & 0xff;
	arr[num++] = (port_a >> 8) & 0xff;
	arr[num++] = port_a & 0xff;
	/* NAA-5, Target port group identifier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x95;	/* piv=1, target port group id */
	arr[num++] = 0x0;
	arr[num++] = 0x4;
	arr[num++] = 0;
	arr[num++] = 0;
	arr[num++] = (port_group_id >> 8) & 0xff;
	arr[num++] = port_group_id & 0xff;
	/* NAA-5, Target device identifier */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0xa3;	/* piv=1, target device, naa */
	arr[num++] = 0x0;
	arr[num++] = 0x8;
	arr[num++] = 0x52;	/* naa-5, company id=0x222222 (fake) */
	arr[num++] = 0x22;
	arr[num++] = 0x22;
	arr[num++] = 0x20;
	arr[num++] = (target_dev_id >> 24);
	arr[num++] = (target_dev_id >> 16) & 0xff;
	arr[num++] = (target_dev_id >> 8) & 0xff;
	arr[num++] = target_dev_id & 0xff;
	/* SCSI name string: Target device identifier */
	arr[num++] = 0x63;	/* proto=sas, UTF-8 */
	arr[num++] = 0xa8;	/* piv=1, target device, SCSI name string */
	arr[num++] = 0x0;
	arr[num++] = 24;
	memcpy(arr + num, "naa.52222220", 12);
	num += 12;
	snprintf(b, sizeof(b), "%08X", target_dev_id);
	memcpy(arr + num, b, 8);
	num += 8;
	memset(arr + num, 0, 4);
	num += 4;
	return num;
}