#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int address; int wLine; } ;
typedef  TYPE_1__ YuiMem ;
typedef  int /*<<< orphan*/  GtkToolButton ;

/* Variables and functions */
 int /*<<< orphan*/  yui_mem_update (TYPE_1__*) ; 

__attribute__((used)) static void yui_mem_pagedown_clicked (GtkToolButton * button, YuiMem * ym) {
  ym->address += 2*ym->wLine;
  yui_mem_update(ym);
}