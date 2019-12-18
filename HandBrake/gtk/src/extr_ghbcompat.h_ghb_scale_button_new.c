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
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_ICON_SIZE_BUTTON ; 
 int /*<<< orphan*/ * gtk_scale_button_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static inline GtkWidget *
ghb_scale_button_new(gdouble min, gdouble max, gdouble step,
                     const gchar ** icons)
{
    return gtk_scale_button_new(GHB_ICON_SIZE_BUTTON, min, max, step, icons);
}