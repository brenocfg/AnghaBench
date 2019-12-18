#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  amixdown; } ;
typedef  TYPE_1__ hb_mixdown_t ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  grey_combo_box_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* hb_mixdown_get_next (TYPE_1__ const*) ; 
 int /*<<< orphan*/  hb_mixdown_has_codec_support (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ghb_mix_opts_filter(GtkComboBox *combo, gint acodec)
{
    g_debug("ghb_mix_opts_filter()\n");

    const hb_mixdown_t *mix;
    for (mix = hb_mixdown_get_next(NULL); mix != NULL;
         mix = hb_mixdown_get_next(mix))
    {
        grey_combo_box_item(combo, mix->amixdown,
                !hb_mixdown_has_codec_support(mix->amixdown, acodec));
    }
}