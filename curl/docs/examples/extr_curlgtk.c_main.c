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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/ * Bar ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SHADOW_IN ; 
 int /*<<< orphan*/  GTK_SHADOW_OUT ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*) ; 
 int /*<<< orphan*/  gdk_threads_enter () ; 
 int /*<<< orphan*/  gdk_threads_leave () ; 
 scalar_t__ gtk_adjustment_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_frame_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_shadow_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/ * gtk_progress_bar_new_with_adjustment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_thread ; 

int main(int argc, char **argv)
{
  GtkWidget *Window, *Frame, *Frame2;
  GtkAdjustment *adj;

  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);

  /* Init thread */
  g_thread_init(NULL);

  gtk_init(&argc, &argv);
  Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  Frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(Frame), GTK_SHADOW_OUT);
  gtk_container_add(GTK_CONTAINER(Window), Frame);
  Frame2 = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(Frame2), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(Frame), Frame2);
  gtk_container_set_border_width(GTK_CONTAINER(Frame2), 5);
  adj = (GtkAdjustment*)gtk_adjustment_new(0, 0, 100, 0, 0, 0);
  Bar = gtk_progress_bar_new_with_adjustment(adj);
  gtk_container_add(GTK_CONTAINER(Frame2), Bar);
  gtk_widget_show_all(Window);

  if(!g_thread_create(&my_thread, argv[1], FALSE, NULL) != 0)
    g_warning("can't create the thread");


  gdk_threads_enter();
  gtk_main();
  gdk_threads_leave();
  return 0;
}