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
 int /*<<< orphan*/  VC_FILESYS_READ ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_2__ vc_filesys_client ; 
 int vc_vchi_msg_bulk_read (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int vc_filesys_read(int fildes, void *buf, unsigned int nbyte)
{
   int bulk_bytes = 0;
   int actual_read = 0;
   int total_byte = 0;
   uint8_t* ptr = (uint8_t*)buf;

   if (nbyte == 0) {
      return 0;
   }

   if(lock_obtain() == 0)
   {
      do {
         bulk_bytes = nbyte > FILESERV_MAX_BULK ? FILESERV_MAX_BULK : nbyte;

         //we overwrite the response here so fill in data again
         vc_filesys_client.fileserv_msg.params[0] = (uint32_t)fildes;
         vc_filesys_client.fileserv_msg.params[1] = 0xffffffffU;        // offset: use -1 to indicate no offset

         actual_read = vc_vchi_msg_bulk_read(&vc_filesys_client.fileserv_msg , VC_FILESYS_READ, (uint32_t)bulk_bytes, (uint8_t*)ptr);

         if(bulk_bytes != actual_read) {
            if(actual_read < 0)
               total_byte = -1;
            else
               total_byte += actual_read;
            //exit loop
            break;
         }

         ptr+=bulk_bytes;
         nbyte -= actual_read;
         total_byte += actual_read;
      }while(nbyte > 0);

      lock_release();
   }

   return total_byte;
}