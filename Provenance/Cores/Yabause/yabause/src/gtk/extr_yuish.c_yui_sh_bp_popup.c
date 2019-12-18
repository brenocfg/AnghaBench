#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_6__ {int /*<<< orphan*/  bp_menu; } ;
typedef  TYPE_1__ YuiSh ;
struct TYPE_7__ {scalar_t__ type; int button; int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkMenu ;
typedef  TYPE_3__ GdkEventButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDK_BUTTON_PRESS ; 
 int /*<<< orphan*/ * GTK_MENU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_menu_popup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

gint yui_sh_bp_popup(GtkWidget * widget, GdkEventButton * event, gpointer data)
{
  GtkMenu *menu;
  GdkEventButton *event_button;
  YuiSh * sh2 = data;

  g_return_val_if_fail (data != NULL, FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  menu = GTK_MENU(sh2->bp_menu);

  if (event->type == GDK_BUTTON_PRESS) {
      event_button = (GdkEventButton *) event;
      if (event_button->button == 3) {
	  gtk_menu_popup (menu, NULL, NULL, NULL, NULL, event_button->button, event_button->time);
      }
  }

  return FALSE;
}