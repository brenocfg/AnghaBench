#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {int socket; } ;
struct TYPE_9__ {int /*<<< orphan*/  fifo_buffer; TYPE_1__ conn; } ;
typedef  TYPE_2__ rsound_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  RSD_DEBUG (char*,...) ; 
 int /*<<< orphan*/  RSD_ERR (char*) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NBIO ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,char*,int) ; 
 int fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_socketclose (int) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsd_free (TYPE_2__*) ; 
 scalar_t__ rsd_start (TYPE_2__*) ; 
 scalar_t__ rsnd_close_ctl (TYPE_2__*) ; 
 scalar_t__ rsnd_send_chunk (int,char*,int,int) ; 
 int /*<<< orphan*/  rsnd_stop_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int rsd_exec(rsound_t *rsound)
{
   retro_assert(rsound != NULL);
   RSD_DEBUG("[RSound] rsd_exec().\n");

   // Makes sure we have a working connection
   if ( rsound->conn.socket < 0 )
   {
      RSD_DEBUG("[RSound] Calling rsd_start().\n");
      if ( rsd_start(rsound) < 0 )
      {
         RSD_ERR("[RSound] rsd_start() failed.\n");
         return -1;
      }
   }

   RSD_DEBUG("[RSound] Closing ctl.\n");
   if ( rsnd_close_ctl(rsound) < 0 )
      return -1;

   int fd = rsound->conn.socket;
   RSD_DEBUG("[RSound] Socket: %d.\n", fd);

   rsnd_stop_thread(rsound);

#if defined(__CELLOS_LV2__)
   int i = 0;
   setsockopt(rsound->conn.socket, SOL_SOCKET, SO_NBIO, &i, sizeof(int));
#else
   fcntl(rsound->conn.socket, F_SETFL, O_NONBLOCK);
#endif

   // Flush the buffer

   if ( fifo_read_avail(rsound->fifo_buffer) > 0 )
   {
      char buffer[fifo_read_avail(rsound->fifo_buffer)];
      fifo_read(rsound->fifo_buffer, buffer, sizeof(buffer));
      if ( rsnd_send_chunk(fd, buffer, sizeof(buffer), 1) != (ssize_t)sizeof(buffer) )
      {
         RSD_DEBUG("[RSound] Failed flushing buffer.\n");
         net_socketclose(fd);
         return -1;
      }
   }

   RSD_DEBUG("[RSound] Returning from rsd_exec().\n");
   rsd_free(rsound);
   return fd;
}