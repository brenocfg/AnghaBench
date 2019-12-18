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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int gint ;

/* Variables and functions */

void
ghb_screen_par(signal_user_data_t *ud, gint *par_n, gint *par_d)
{
    // Assume 1:1
    // I could get it from GtkWindow->GdkScreen monitor methods.
    // But it's going to be 1:1 anyway, so why bother.
    *par_n = 1;
    *par_d = 1;
}