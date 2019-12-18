#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ transfer_len ;
struct TYPE_6__ {int cur_xid; int /*<<< orphan*/  response_event; int /*<<< orphan*/  open_handle; } ;
struct TYPE_5__ {int xid; scalar_t__ cmd_code; scalar_t__* params; scalar_t__ data; } ;
typedef  TYPE_1__ FILESERV_MSG_T ;

/* Variables and functions */
 scalar_t__ FILESERV_BULK_READ ; 
 scalar_t__ FILESERV_MAX_BULK ; 
 scalar_t__ FILESERV_MAX_DATA ; 
 scalar_t__ FILESERV_RESP_ERROR ; 
 scalar_t__ VCHI_BULK_ALIGN_NBYTES (int /*<<< orphan*/ *) ; 
 int VCHI_BULK_GRANULARITY ; 
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__ vc_filesys_client ; 
 scalar_t__ vchi_bulk_queue_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vchi_msg_queue (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

__attribute__((used)) static int vc_vchi_msg_bulk_write(FILESERV_MSG_T* msg, uint16_t cmd_id, uint32_t transfer_len, uint8_t* send_addr )
{
   uint32_t i;
   int msg_len;
   uint32_t align_bytes = 0;
   uint32_t bulk_end_bytes = 0;
   uint32_t bulk_bytes = 0;
   int num_bytes_written = -1;

   //this is current file_io_buffer size so assuming never more than this
   //otherwise we will split the read into chunks
   if(!vcos_verify(transfer_len <= FILESERV_MAX_BULK))
      return -1;

   i = vc_filesys_client.cur_xid + 1;
   i &= 0x7fffffffUL;
   vc_filesys_client.cur_xid = i;

   msg->xid = vc_filesys_client.cur_xid;

   //fill in cmd id VC_FILESYS_OPEN etc
   msg->cmd_code = cmd_id;

   msg->params[2] = transfer_len;

   //24 comes from the static size of FILESERV_MSG_T
   msg_len = 24;

   //put it all in one msg
   if(transfer_len <= FILESERV_MAX_DATA) {
      memcpy(msg->data, send_addr, transfer_len);
      msg->params[3] = 0;
      msg_len += transfer_len;
      //send request to write to host
      if(vchi_msg_queue( vc_filesys_client.open_handle, msg, (uint32_t)msg_len, VCHI_FLAGS_BLOCK_UNTIL_QUEUED, NULL ) != 0)
         return -1;

      // wait to receive response
      if(vcos_event_wait(&vc_filesys_client.response_event) == VCOS_SUCCESS &&
         msg->cmd_code != FILESERV_RESP_ERROR && msg->params[0] == transfer_len)
      {
         //vc_fs_message_handler copies resp into outgoing msg struct
         num_bytes_written = (int)msg->params[0];
      }
   }
   else {
      //required to make send_addr for bulk
      align_bytes = VCHI_BULK_ALIGN_NBYTES(send_addr);

// Make this code conditional to stop Coverity complaining about dead code
#if VCHI_BULK_ALIGN > 1
      //copy vc_align bytes to msg->data, send_addr ready for bulk
      if(align_bytes) {
         msg->params[3] = align_bytes;
         memcpy(msg->data, send_addr, align_bytes);
         transfer_len -= align_bytes;
         send_addr += align_bytes;
         msg_len += align_bytes;
      }
      else
#endif
         msg->params[3] = 0;

      // need to ensure we have the appropriate alignment
      bulk_bytes = (transfer_len)&(~(VCHI_BULK_GRANULARITY-1));

      bulk_end_bytes = transfer_len-bulk_bytes;

      if(bulk_end_bytes) {
         memcpy(msg->data+align_bytes, send_addr+bulk_bytes, bulk_end_bytes);
         msg_len += bulk_end_bytes;
      }

      //send request to write to host
      if(vchi_msg_queue( vc_filesys_client.open_handle, msg, (uint32_t)msg_len, VCHI_FLAGS_BLOCK_UNTIL_QUEUED, NULL ) != 0)
         return -1;

      //send bulk VCHI_FLAGS_BLOCK_UNTIL_QUEUED is ok because we wait for response msg with actual length written
      if(vchi_bulk_queue_transmit( vc_filesys_client.open_handle,
                                   send_addr,
                                   bulk_bytes,
                                   VCHI_FLAGS_BLOCK_UNTIL_QUEUED,
                                   NULL ) != 0)
         return -1;

      // wait to receive response sent by filsys_task_func
      if(vcos_event_wait(&vc_filesys_client.response_event) == VCOS_SUCCESS && msg->cmd_code == FILESERV_BULK_READ)
         num_bytes_written = (int)msg->params[0];
   }

   return num_bytes_written;
}