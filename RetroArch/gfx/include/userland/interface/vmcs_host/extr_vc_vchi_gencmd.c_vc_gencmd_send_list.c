#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {int num_connections; int /*<<< orphan*/  command_buffer; int /*<<< orphan*/ * open_handle; } ;

/* Variables and functions */
 int GENCMD_MAX_LENGTH ; 
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 TYPE_1__ gencmd_client ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 int /*<<< orphan*/  release_gencmd_service () ; 
 int /*<<< orphan*/  use_gencmd_service () ; 
 int vchi_msg_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vsnprintf (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 

int vc_gencmd_send_list ( const char *format, va_list a )
{
   int success = -1;

   // Obtain the lock and keep it so no one else can butt in while we await the response.
   if(lock_obtain() == 0)
   {
      int length = vsnprintf( gencmd_client.command_buffer, GENCMD_MAX_LENGTH, format, a );

      if (length >= 0 && length < GENCMD_MAX_LENGTH)
      {
         int i;
         use_gencmd_service();
         for( i=0; i<gencmd_client.num_connections; i++ ) {
            success = vchi_msg_queue( gencmd_client.open_handle[i],
                                           gencmd_client.command_buffer,
                                           length+1,
                                           VCHI_FLAGS_BLOCK_UNTIL_QUEUED, NULL );

            if(success == 0)
            { // only want to send on one connection, so break on success
               break;
            }
         }
         release_gencmd_service();
      }

      lock_release();
   }

   return success;
}