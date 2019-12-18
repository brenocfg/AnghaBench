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
struct TYPE_3__ {int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_1__ YuiSh ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  SH2Step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_window_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_sh_step( GtkWidget* widget, YuiSh * sh2 ) {

  SH2Step(sh2->debugsh);
  yui_window_invalidate( yui ); /* update all dialogs, including us */
}