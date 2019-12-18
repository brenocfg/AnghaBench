#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkComboBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_mix_opts_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mix_opts_set(signal_user_data_t *ud, const gchar *name,
             void *opts, const void* data)
{
    (void)opts; // Silence "unused variable" warning
    (void)data; // Silence "unused variable" warning

    GtkComboBox *combo = GTK_COMBO_BOX(GHB_WIDGET(ud->builder, name));
    ghb_mix_opts_set(combo);
}