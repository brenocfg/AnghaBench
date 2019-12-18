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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_PROGRESS_BAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SHADOW_IN ; 
 int /*<<< orphan*/  GTK_SHADOW_OUT ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cb_delete ; 
 int /*<<< orphan*/  create_thread ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_set_data (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*) ; 
 int /*<<< orphan*/  gdk_threads_enter () ; 
 int /*<<< orphan*/  gdk_threads_init () ; 
 int /*<<< orphan*/  gdk_threads_leave () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_frame_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_shadow_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/ * gtk_progress_bar_new () ; 
 int /*<<< orphan*/  gtk_progress_bar_pulse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pulse_bar ; 

int main(int argc, char **argv)
{
  GtkWidget *top_window, *outside_frame, *inside_frame, *progress_bar;

  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);

  /* Init thread */
  g_thread_init(NULL);
  gdk_threads_init();
  gdk_threads_enter();

  gtk_init(&argc, &argv);

  /* Base window */
  top_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  /* Frame */
  outside_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(outside_frame), GTK_SHADOW_OUT);
  gtk_container_add(GTK_CONTAINER(top_window), outside_frame);

  /* Frame */
  inside_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(inside_frame), GTK_SHADOW_IN);
  gtk_container_set_border_width(GTK_CONTAINER(inside_frame), 5);
  gtk_container_add(GTK_CONTAINER(outside_frame), inside_frame);

  /* Progress bar */
  progress_bar = gtk_progress_bar_new();
  gtk_progress_bar_pulse(GTK_PROGRESS_BAR (progress_bar));
  /* Make uniform pulsing */
  gint pulse_ref = g_timeout_add(300, pulse_bar, progress_bar);
  g_object_set_data(G_OBJECT(progress_bar), "pulse_id",
                    GINT_TO_POINTER(pulse_ref));
  gtk_container_add(GTK_CONTAINER(inside_frame), progress_bar);

  gtk_widget_show_all(top_window);
  printf("gtk_widget_show_all\n");

  g_signal_connect(G_OBJECT (top_window), "delete-event",
                   G_CALLBACK(cb_delete), NULL);

  if(!g_thread_create(&create_thread, progress_bar, FALSE, NULL) != 0)
    g_warning("can't create the thread");

  gtk_main();
  gdk_threads_leave();
  printf("gdk_threads_leave\n");

  return 0;
}