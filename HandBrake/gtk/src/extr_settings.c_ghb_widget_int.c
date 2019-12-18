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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ ghb_value_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_widget_value (int /*<<< orphan*/ *) ; 

gint
ghb_widget_int(GtkWidget *widget)
{
    GhbValue *value;
    gint ival;

    value = ghb_widget_value(widget);
    ival = (gint)ghb_value_get_int(value);
    ghb_value_free(&value);
    return ival;
}