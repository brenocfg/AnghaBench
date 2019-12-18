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
struct TYPE_2__ {int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct ipr_vpd {int /*<<< orphan*/  sn; TYPE_1__ vpids; } ;
struct ipr_hostrcb {int dummy; } ;

/* Variables and functions */
 int IPR_PROD_ID_LEN ; 
 int IPR_SERIAL_NUM_LEN ; 
 int IPR_VENDOR_ID_LEN ; 
 int /*<<< orphan*/  ipr_hcam_err (struct ipr_hostrcb*,char*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strip_and_pad_whitespace (int,char*) ; 

__attribute__((used)) static void ipr_log_vpd_compact(char *prefix, struct ipr_hostrcb *hostrcb,
				struct ipr_vpd *vpd)
{
	char buffer[IPR_VENDOR_ID_LEN + IPR_PROD_ID_LEN + IPR_SERIAL_NUM_LEN + 3];
	int i = 0;

	memcpy(buffer, vpd->vpids.vendor_id, IPR_VENDOR_ID_LEN);
	i = strip_and_pad_whitespace(IPR_VENDOR_ID_LEN - 1, buffer);

	memcpy(&buffer[i], vpd->vpids.product_id, IPR_PROD_ID_LEN);
	i = strip_and_pad_whitespace(i + IPR_PROD_ID_LEN - 1, buffer);

	memcpy(&buffer[i], vpd->sn, IPR_SERIAL_NUM_LEN);
	buffer[IPR_SERIAL_NUM_LEN + i] = '\0';

	ipr_hcam_err(hostrcb, "%s VPID/SN: %s\n", prefix, buffer);
}