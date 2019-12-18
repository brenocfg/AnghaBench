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
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkBox ;

/* Variables and functions */
 scalar_t__ GTK_ALIGN_FILL ; 
 int /*<<< orphan*/  GTK_ORIENTABLE (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_ORIENTATION_HORIZONTAL ; 
 scalar_t__ gtk_orientable_get_orientation (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_widget_get_halign (int /*<<< orphan*/ *) ; 
 int gtk_widget_get_hexpand (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_widget_get_valign (int /*<<< orphan*/ *) ; 
 int gtk_widget_get_vexpand (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ghb_get_expand_fill(GtkBox * box, GtkWidget * child,
                                       gboolean *expand, gboolean *fill)
{
    if (gtk_orientable_get_orientation(GTK_ORIENTABLE(box)) ==
        GTK_ORIENTATION_HORIZONTAL)
    {
        *expand = gtk_widget_get_hexpand(child);
        *fill   = gtk_widget_get_halign(child) == GTK_ALIGN_FILL;
    }
    else
    {
        *expand = gtk_widget_get_vexpand(child);
        *fill   = gtk_widget_get_valign(child) == GTK_ALIGN_FILL;
    }
}