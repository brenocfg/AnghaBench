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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum bfi_asic_gen { ____Placeholder_bfi_asic_gen } bfi_asic_gen ;

/* Variables and functions */
#define  BFI_ASIC_GEN_CB 130 
#define  BFI_ASIC_GEN_CT 129 
#define  BFI_ASIC_GEN_CT2 128 
 int /*<<< orphan*/ * bfi_image_cb_get_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfi_image_ct2_get_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfi_image_ct_get_chunk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32*
bfa_cb_image_get_chunk(enum bfi_asic_gen asic_gen, u32 off)
{
	switch (asic_gen) {
	case BFI_ASIC_GEN_CB:
		return bfi_image_cb_get_chunk(off);
		break;
	case BFI_ASIC_GEN_CT:
		return bfi_image_ct_get_chunk(off);
		break;
	case BFI_ASIC_GEN_CT2:
		return bfi_image_ct2_get_chunk(off);
		break;
	default:
		return NULL;
	}
}