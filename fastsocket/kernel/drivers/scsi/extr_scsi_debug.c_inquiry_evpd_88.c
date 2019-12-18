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

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inquiry_evpd_88(unsigned char * arr, int target_dev_id)
{
	int num = 0;
	int port_a, port_b;

	port_a = target_dev_id + 1;
	port_b = port_a + 1;
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x1;	/* relative port 1 (primary) */
	memset(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identifier (A) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	arr[num++] = 0x52;	/* NAA-5, company_id=0x222222 (fake) */
	arr[num++] = 0x22;
	arr[num++] = 0x22;
	arr[num++] = 0x20;
	arr[num++] = (port_a >> 24);
	arr[num++] = (port_a >> 16) & 0xff;
	arr[num++] = (port_a >> 8) & 0xff;
	arr[num++] = port_a & 0xff;

	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x2;	/* relative port 2 (secondary) */
	memset(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identifier (B) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	arr[num++] = 0x52;	/* NAA-5, company_id=0x222222 (fake) */
	arr[num++] = 0x22;
	arr[num++] = 0x22;
	arr[num++] = 0x20;
	arr[num++] = (port_b >> 24);
	arr[num++] = (port_b >> 16) & 0xff;
	arr[num++] = (port_b >> 8) & 0xff;
	arr[num++] = port_b & 0xff;

	return num;
}