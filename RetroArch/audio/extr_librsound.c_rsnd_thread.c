#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  cond_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  thread; } ;
struct TYPE_9__ {int chunk_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  socket; } ;
struct TYPE_11__ {int conn_type; int total_written; int channels; int rate; int samplesize; int has_written; TYPE_3__ thread; scalar_t__ thread_active; int /*<<< orphan*/  start_time; TYPE_2__ backend_info; TYPE_1__ conn; int /*<<< orphan*/  fifo_buffer; } ;
typedef  TYPE_4__ rsound_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int RSD_CONN_PROTO ; 
 int /*<<< orphan*/  RSD_DEBUG (char*) ; 
 int /*<<< orphan*/  _TEST_CANCEL () ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_get_time_usec () ; 
 int /*<<< orphan*/  rsnd_reset (TYPE_4__*) ; 
 int rsnd_send_chunk (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rsnd_send_info_query (TYPE_4__*) ; 
 int /*<<< orphan*/  rsnd_update_server_info (TYPE_4__*) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsnd_thread ( void * thread_data )
{
   /* We share data between thread and callable functions */
   rsound_t *rd = thread_data;
   int rc;
   char buffer[rd->backend_info.chunk_size];

   /* Plays back data as long as there is data in the buffer. Else, sleep until it can. */
   /* Two (;;) for loops! :3 Beware! */
   for (;;)
   {
      for(;;)
      {
         _TEST_CANCEL();

         // We ask the server to send its latest backend data. Do not really care about errors atm.
         // We only bother to check after 1 sec of audio has been played, as it might be quite inaccurate in the start of the stream.
         if ( (rd->conn_type & RSD_CONN_PROTO) && (rd->total_written > rd->channels * rd->rate * rd->samplesize) )
         {
            rsnd_send_info_query(rd);
            rsnd_update_server_info(rd);
         }

         /* If the buffer is empty or we've stopped the stream, jump out of this for loop */
         slock_lock(rd->thread.mutex);
         if ( fifo_read_avail(rd->fifo_buffer) < rd->backend_info.chunk_size || !rd->thread_active )
         {
            slock_unlock(rd->thread.mutex);
            break;
         }
         slock_unlock(rd->thread.mutex);

         _TEST_CANCEL();
         slock_lock(rd->thread.mutex);
         fifo_read(rd->fifo_buffer, buffer, sizeof(buffer));
         slock_unlock(rd->thread.mutex);
         rc = rsnd_send_chunk(rd->conn.socket, buffer, sizeof(buffer), 1);

         /* If this happens, we should make sure that subsequent and current calls to rsd_write() will fail. */
         if ( rc != (int)rd->backend_info.chunk_size )
         {
            _TEST_CANCEL();
            rsnd_reset(rd);

            /* Wakes up a potentially sleeping fill_buffer() */
            scond_signal(rd->thread.cond);

            /* This thread will not be joined, so detach. */
            sthread_detach(rd->thread.thread);
            return;
         }

         /* If this was the first write, set the start point for the timer. */
         if ( !rd->has_written )
         {
            slock_lock(rd->thread.mutex);
            rd->start_time = rsnd_get_time_usec();
            rd->has_written = 1;
            slock_unlock(rd->thread.mutex);
         }

         /* Increase the total_written counter. Used in rsnd_drain() */
         slock_lock(rd->thread.mutex);
         rd->total_written += rc;
         slock_unlock(rd->thread.mutex);

         /* Buffer has decreased, signal fill_buffer() */
         scond_signal(rd->thread.cond);

      }

      /* If we're still good to go, sleep. We are waiting for fill_buffer() to fill up some data. */

      if ( rd->thread_active )
      {
         // There is a very slim change of getting a deadlock using the cond_wait scheme.
         // This solution is rather dirty, but avoids complete deadlocks at the very least.

         slock_lock(rd->thread.cond_mutex);
         scond_signal(rd->thread.cond);

         if ( rd->thread_active )
         {
            RSD_DEBUG("[RSound] Thread going to sleep.\n");
            scond_wait(rd->thread.cond, rd->thread.cond_mutex);
            RSD_DEBUG("[RSound] Thread woke up.\n");
         }

         slock_unlock(rd->thread.cond_mutex);
         RSD_DEBUG("[RSound] Thread unlocked cond_mutex.\n");
      }
      /* Abort request, chap. */
      else
      {
         scond_signal(rd->thread.cond);
         return;
      }

   }
}