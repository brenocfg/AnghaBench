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
struct bfi_ioc_image_hdr {scalar_t__* md5sum; } ;
struct bfa_ioc {int dummy; } ;

/* Variables and functions */
 int BFI_IOC_MD5SUM_SZ ; 
 scalar_t__ bfa_cb_image_get_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc*) ; 

bool
bfa_nw_ioc_fwver_cmp(struct bfa_ioc *ioc, struct bfi_ioc_image_hdr *fwhdr)
{
	struct bfi_ioc_image_hdr *drv_fwhdr;
	int i;

	drv_fwhdr = (struct bfi_ioc_image_hdr *)
		bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

	for (i = 0; i < BFI_IOC_MD5SUM_SZ; i++) {
		if (fwhdr->md5sum[i] != drv_fwhdr->md5sum[i])
			return false;
	}

	return true;
}