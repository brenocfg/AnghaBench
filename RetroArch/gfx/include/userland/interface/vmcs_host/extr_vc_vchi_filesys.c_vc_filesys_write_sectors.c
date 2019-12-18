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
typedef  long uint32_t ;
struct TYPE_3__ {long* params; scalar_t__ cmd_code; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; int /*<<< orphan*/  response_event; int /*<<< orphan*/  open_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESERV_MAX_BULK ; 
 long FILESERV_MAX_BULK_SECTOR ; 
 scalar_t__ FILESERV_RESP_OK ; 
 long FILESERV_SECTOR_LENGTH ; 
 int FS_MAX_PATH ; 
 int VCHI_BULK_ALIGN ; 
 int /*<<< orphan*/  VCHI_BULK_ROUND_UP (long) ; 
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_DATA_READ ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  VC_FILESYS_WRITE_SECTORS ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_bulk_queue_transmit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vchi_msg_stub_noblock (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 

int vc_filesys_write_sectors(const char *path, uint32_t sector_num, char *sectors, uint32_t num_sectors, uint32_t *sectors_written)
{
   uint32_t align_bytes = 0;
   char* bulk_addr = sectors;
   int len;
   int ret = -1;

   len = (int) strlen(path);
   if((len = (int) strlen(path)) < FS_MAX_PATH && lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = sector_num;
      vc_filesys_client.fileserv_msg.params[1] = num_sectors;

      //required to make buffer aligned for bulk
      align_bytes = ((unsigned long)sectors & (VCHI_BULK_ALIGN-1));
      vc_filesys_client.fileserv_msg.params[2] = align_bytes;

      //copy path at end of any alignbytes
      strncpy(((char *)vc_filesys_client.fileserv_msg.data), path, FS_MAX_PATH);

      //we send write request
      if (vchi_msg_stub_noblock(&vc_filesys_client.fileserv_msg, VC_FILESYS_WRITE_SECTORS, 16+len+1) == 0)
      {
         if(align_bytes) {
            //note we are cheating and going backward to make addr aligned and sending more data...
            bulk_addr -= align_bytes;
         }

         while(num_sectors) {
            uint32_t bulk_sectors = (num_sectors > FILESERV_MAX_BULK_SECTOR) ? (uint32_t)FILESERV_MAX_BULK_SECTOR : num_sectors;
            //we send some extra data at the start
            if(vchi_bulk_queue_transmit( vc_filesys_client.open_handle, bulk_addr,
                                         VCHI_BULK_ROUND_UP((bulk_sectors*FILESERV_SECTOR_LENGTH)+align_bytes),
                                         VCHI_FLAGS_BLOCK_UNTIL_DATA_READ, NULL) != 0)
               break;

            //go to next ALIGNED address
            bulk_addr += FILESERV_MAX_BULK;
            num_sectors -= bulk_sectors;
         }

         // now wait to receive resp from original msg...
         if(vcos_event_wait(&vc_filesys_client.response_event) == VCOS_SUCCESS && vc_filesys_client.fileserv_msg.cmd_code == FILESERV_RESP_OK)
         {
            *sectors_written = vc_filesys_client.fileserv_msg.params[0];
            ret = 0;
         }
         else
         {
            //error code in [0]
            *sectors_written = vc_filesys_client.fileserv_msg.params[1];
            ret = vc_filesys_client.fileserv_msg.params[0];
         }
      }

      lock_release();
   }

   return ret;
}