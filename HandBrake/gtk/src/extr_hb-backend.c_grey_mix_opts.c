#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  amixdown; } ;
typedef  TYPE_2__ hb_mixdown_t ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  grey_builder_combo_box_item (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* hb_mixdown_get_next (TYPE_2__ const*) ; 
 int /*<<< orphan*/  hb_mixdown_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grey_mix_opts(signal_user_data_t *ud, gint acodec, gint64 layout)
{
    g_debug("grey_mix_opts()\n");

    const hb_mixdown_t *mix;
    for (mix = hb_mixdown_get_next(NULL); mix != NULL;
         mix = hb_mixdown_get_next(mix))
    {
        grey_builder_combo_box_item(ud->builder, "AudioMixdown", mix->amixdown,
                !hb_mixdown_is_supported(mix->amixdown, acodec, layout));
    }
}