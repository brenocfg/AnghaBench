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
struct brcms_ucode {scalar_t__ bcm43xx_bomminor; scalar_t__ bcm43xx_bommajor; scalar_t__ bcm43xx_24_lcn; scalar_t__ bcm43xx_16_mimo; scalar_t__ d11n0initvals16; scalar_t__ d11n0bsinitvals16; scalar_t__ d11n0absinitvals16; scalar_t__ d11lcn2initvals24; scalar_t__ d11lcn2bsinitvals24; scalar_t__ d11lcn1initvals24; scalar_t__ d11lcn1bsinitvals24; scalar_t__ d11lcn0initvals24; scalar_t__ d11lcn0bsinitvals24; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_ucode_free_buf (void*) ; 

void brcms_ucode_data_free(struct brcms_ucode *ucode)
{
	brcms_ucode_free_buf((void *)ucode->d11lcn0bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn0initvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn1bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn1initvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn2bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn2initvals24);
	brcms_ucode_free_buf((void *)ucode->d11n0absinitvals16);
	brcms_ucode_free_buf((void *)ucode->d11n0bsinitvals16);
	brcms_ucode_free_buf((void *)ucode->d11n0initvals16);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_16_mimo);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_24_lcn);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_bommajor);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_bomminor);
}