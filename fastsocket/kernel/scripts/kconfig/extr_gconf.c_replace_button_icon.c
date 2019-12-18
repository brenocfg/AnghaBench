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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/ * bg; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkToolButton ;
typedef  TYPE_1__ GtkStyle ;
typedef  int /*<<< orphan*/  GladeXML ;
typedef  int /*<<< orphan*/  GdkPixmap ;
typedef  int /*<<< orphan*/  GdkDrawable ;
typedef  int /*<<< orphan*/  GdkBitmap ;

/* Variables and functions */
 size_t GTK_STATE_NORMAL ; 
 int /*<<< orphan*/ * GTK_TOOL_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdk_pixmap_create_from_xpm_d (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  glade_xml_get_widget (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_image_new_from_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tool_button_set_icon_widget (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

void replace_button_icon(GladeXML * xml, GdkDrawable * window,
			 GtkStyle * style, gchar * btn_name, gchar ** xpm)
{
	GdkPixmap *pixmap;
	GdkBitmap *mask;
	GtkToolButton *button;
	GtkWidget *image;

	pixmap = gdk_pixmap_create_from_xpm_d(window, &mask,
					      &style->bg[GTK_STATE_NORMAL],
					      xpm);

	button = GTK_TOOL_BUTTON(glade_xml_get_widget(xml, btn_name));
	image = gtk_image_new_from_pixmap(pixmap, mask);
	gtk_widget_show(image);
	gtk_tool_button_set_icon_widget(button, image);
}