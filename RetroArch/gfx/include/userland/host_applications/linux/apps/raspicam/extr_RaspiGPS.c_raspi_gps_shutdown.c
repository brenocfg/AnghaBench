#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ gpsd_connected; } ;
struct TYPE_5__ {int terminated; int /*<<< orphan*/  gps_cache_mutex; TYPE_1__ gpsd; int /*<<< orphan*/  gps_reader_thread; scalar_t__ gps_reader_thread_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  disconnect_gpsd (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ gps_reader_data ; 
 int /*<<< orphan*/  libgps_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void raspi_gps_shutdown(int verbose)
{
   gps_reader_data.terminated = 1;

   if (gps_reader_data.gps_reader_thread_ok)
   {
      if (verbose)
         fprintf(stderr, "Waiting for GPS reader thread to terminate\n");

      pthread_join(gps_reader_data.gps_reader_thread, NULL);
   }
   if (verbose && gps_reader_data.gpsd.gpsd_connected)
      fprintf(stderr, "Closing gpsd connection\n\n");

   disconnect_gpsd(&gps_reader_data.gpsd);

   libgps_unload(&gps_reader_data.gpsd);

   pthread_mutex_destroy(&gps_reader_data.gps_cache_mutex);
}