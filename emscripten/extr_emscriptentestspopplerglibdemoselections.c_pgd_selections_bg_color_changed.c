#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_6__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_7__ {TYPE_1__ background_color; } ;
typedef  TYPE_2__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkColorButton ;
typedef  TYPE_3__ GdkColor ;
typedef  int /*<<< orphan*/  GParamSpec ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COLOR_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_color_button_get_color (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
pgd_selections_bg_color_changed (GtkColorButton    *button,
				 GParamSpec        *pspec,
				 PgdSelectionsDemo *demo)
{
	GdkColor color;

	gtk_color_button_get_color (GTK_COLOR_BUTTON (button), &color);
	demo->background_color.red = color.red;
	demo->background_color.green = color.green;
	demo->background_color.blue = color.blue;
}