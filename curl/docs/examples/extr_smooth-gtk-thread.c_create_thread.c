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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (void*) ; 
 int NUMT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  g_object_get_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_source_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (void*) ; 
 int num_urls ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pull_one_url ; 
 int /*<<< orphan*/  stderr ; 
 char** urls ; 

void *create_thread(void *progress_bar)
{
  pthread_t tid[NUMT];
  int i;

  /* Make sure I don't create more threads than urls. */
  for(i = 0; i < NUMT && i < num_urls ; i++) {
    int error = pthread_create(&tid[i],
                               NULL, /* default attributes please */
                               pull_one_url,
                               NULL);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, urls[i]);
  }

  /* Wait for all threads to terminate. */
  for(i = 0; i < NUMT && i < num_urls; i++) {
    pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }

  /* This stops the pulsing if you have it turned on in the progress bar
     section */
  g_source_remove(GPOINTER_TO_INT(g_object_get_data(G_OBJECT(progress_bar),
                                                    "pulse_id")));

  /* This destroys the progress bar */
  gtk_widget_destroy(progress_bar);

  /* [Un]Comment this out to kill the program rather than pushing close. */
  /* gtk_main_quit(); */


  return NULL;

}