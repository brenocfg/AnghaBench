#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* params; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 unsigned int FILESERV_MAX_BULK ; 
 int /*<<< orphan*/  VC_FILESYS_WRITE ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_2__ vc_filesys_client ; 
 int vc_vchi_msg_bulk_write (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int vc_filesys_write(int fildes, const void *buf, unsigned int nbyte)
{
   int num_wrt = 0;
   int bulk_bytes = 0;
   int actual_written = 0;
   uint8_t *ptr = (uint8_t*) buf;

   if (nbyte == 0) {
      return 0;
   }

   if(lock_obtain() == 0)
   {
      //will split the read into 4K chunks based on vc fwrite buffer size array size
      //we will make this more dynamic later
      do {
         bulk_bytes = nbyte > FILESERV_MAX_BULK ? FILESERV_MAX_BULK : nbyte;

         //we overwrite the response here so fill in data again
         vc_filesys_client.fileserv_msg.params[0] = (uint32_t)fildes;
         vc_filesys_client.fileserv_msg.params[1] = 0xffffffffU;        // offset: use -1 to indicate no offset

         actual_written = vc_vchi_msg_bulk_write(&vc_filesys_client.fileserv_msg , VC_FILESYS_WRITE, (uint32_t)bulk_bytes, (uint8_t*)ptr);

         if(bulk_bytes != actual_written) {
            if(actual_written < 0)
               num_wrt = -1;
            else
               num_wrt += actual_written;
            break;
         }

         ptr+=bulk_bytes;
         nbyte -= actual_written;
         num_wrt += actual_written;
      }while(nbyte > 0);

      lock_release();
   }

   return num_wrt;
}