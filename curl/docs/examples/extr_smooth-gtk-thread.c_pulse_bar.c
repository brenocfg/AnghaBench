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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gdk_threads_enter () ; 
 int /*<<< orphan*/  gdk_threads_leave () ; 
 int /*<<< orphan*/  gtk_progress_bar_pulse (int /*<<< orphan*/ ) ; 

gboolean pulse_bar(gpointer data)
{
  gdk_threads_enter();
  gtk_progress_bar_pulse(GTK_PROGRESS_BAR (data));
  gdk_threads_leave();

  /* Return true so the function will be called again;
   * returning false removes this timeout function.
   */
  return TRUE;
}