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
typedef  scalar_t__ u32 ;
struct bfi_ioc_image_hdr_s {scalar_t__ signature; scalar_t__ bootenv; } ;
struct bfa_ioc_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ bfa_cb_image_get_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_asic_gen (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_cmp (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_get (struct bfa_ioc_s*,struct bfi_ioc_image_hdr_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,scalar_t__) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 scalar_t__ swab32 (scalar_t__) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_fwver_valid(struct bfa_ioc_s *ioc, u32 boot_env)
{
	struct bfi_ioc_image_hdr_s fwhdr, *drv_fwhdr;

	bfa_ioc_fwver_get(ioc, &fwhdr);
	drv_fwhdr = (struct bfi_ioc_image_hdr_s *)
		bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

	if (fwhdr.signature != cpu_to_le32(drv_fwhdr->signature)) {
		bfa_trc(ioc, fwhdr.signature);
		bfa_trc(ioc, drv_fwhdr->signature);
		return BFA_FALSE;
	}

	if (swab32(fwhdr.bootenv) != boot_env) {
		bfa_trc(ioc, fwhdr.bootenv);
		bfa_trc(ioc, boot_env);
		return BFA_FALSE;
	}

	return bfa_ioc_fwver_cmp(ioc, &fwhdr);
}