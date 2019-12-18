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
struct hda_codec {struct cs_spec* spec; } ;
struct cs_spec {scalar_t__ vendor_nid; } ;

/* Variables and functions */
 scalar_t__ CS420X_VENDOR_NID ; 
 int /*<<< orphan*/  CS_DMIC1_PIN_NID ; 
 int /*<<< orphan*/  CS_DMIC2_PIN_NID ; 
 int /*<<< orphan*/  IDX_BEEP_CFG ; 
 unsigned int cs_vendor_coef_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_vendor_coef_set (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ is_active_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_input_coef(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;
	unsigned int coef;

	/* CS420x has multiple ADC, CS421x has single ADC */
	if (spec->vendor_nid == CS420X_VENDOR_NID) {
		coef = cs_vendor_coef_get(codec, IDX_BEEP_CFG);
		if (is_active_pin(codec, CS_DMIC2_PIN_NID))
			coef |= 1 << 4; /* DMIC2 2 chan on, GPIO1 off */
		if (is_active_pin(codec, CS_DMIC1_PIN_NID))
			coef |= 1 << 3; /* DMIC1 2 chan on, GPIO0 off
					 * No effect if SPDIF_OUT2 is
					 * selected in IDX_SPDIF_CTL.
					*/

		cs_vendor_coef_set(codec, IDX_BEEP_CFG, coef);
	}
}