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
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ghb_init_combo_box (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_combo_box(GtkBuilder *builder, const gchar *name)
{
    GtkComboBox *combo;

    g_debug("init_combo_box() %s\n", name);
    // First modify the combobox model to allow greying out of options
    combo = GTK_COMBO_BOX(GHB_WIDGET(builder, name));
    ghb_init_combo_box(combo);
}