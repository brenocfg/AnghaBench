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
typedef  int /*<<< orphan*/  YuiM68k ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  M68KStep () ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_window_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_m68k_step( GtkWidget* widget, YuiM68k * m68k ) {

  M68KStep();
  yui_window_invalidate( yui ); /* update all dialogs, including us */
}