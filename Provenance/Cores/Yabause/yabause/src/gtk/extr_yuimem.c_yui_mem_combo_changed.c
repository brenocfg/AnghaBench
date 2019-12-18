#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ YuiMem ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 
 TYPE_4__* quickAddress ; 
 int /*<<< orphan*/  yui_mem_update (TYPE_1__*) ; 

__attribute__((used)) static void yui_mem_combo_changed(GtkWidget * w, YuiMem * ym) {

  gint i = gtk_combo_box_get_active( GTK_COMBO_BOX(w) );

  if (i > -1) {
    ym->address = quickAddress[i].address;
    yui_mem_update(ym);
  }
}