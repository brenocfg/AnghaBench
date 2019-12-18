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
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ACODEC_NONE ; 
 int /*<<< orphan*/  ghb_audio_encoder_opts_add_autopass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_audio_encoder_opts_set_with_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ghb_audio_encoder_opts_set(GtkComboBox *combo)
{
    ghb_audio_encoder_opts_set_with_mask(combo, ~0, HB_ACODEC_NONE);
    ghb_audio_encoder_opts_add_autopass(combo);
}