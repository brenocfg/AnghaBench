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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkComboBox ;
typedef  int /*<<< orphan*/  GtkBuilder ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_audio_encoder_opts_set_with_mask (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
audio_encoder_opts_set_with_mask(
    GtkBuilder *builder,
    const gchar *name,
    int mask,
    int neg_mask)
{
    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(builder, name));
    ghb_audio_encoder_opts_set_with_mask(combo, mask, neg_mask);
}