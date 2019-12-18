#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  combo; } ;
typedef  TYPE_1__ YuiRange ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void yui_range_init (YuiRange * yfe) {
        gtk_container_set_border_width(GTK_CONTAINER(yfe), 10);

        yfe->combo = gtk_combo_box_new_text();

        gtk_box_pack_start(GTK_BOX(yfe), yfe->combo, TRUE, TRUE, 0);
}