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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int cur_xid; int /*<<< orphan*/  open_handle; int /*<<< orphan*/  resp_code; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmd_code; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ FILESERV_MSG_T ;

/* Variables and functions */
 int /*<<< orphan*/  FILESERV_RESP_ERROR ; 
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 int VCHI_MAX_MSG_SIZE ; 
 TYPE_4__ vc_filesys_client ; 
 scalar_t__ vchi_msg_queue (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_writebuf_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

__attribute__((used)) static int vchi_msg_stub_noblock(FILESERV_MSG_T* msg, uint16_t cmd_id, int msg_len)
{
   uint32_t i;

   if(!vcos_verify(msg_len <= VCHI_MAX_MSG_SIZE))
      return -1;

   //will get changed by response from command
   vc_filesys_client.resp_code = FILESERV_RESP_ERROR;

   //the top bit is used for host/vc
   i = vc_filesys_client.cur_xid + 1;
   i &= 0x7fffffffUL;
   vc_filesys_client.cur_xid = i;

   //fill in transaction id, used for response identification
   vchi_writebuf_uint32( &(msg->xid), vc_filesys_client.cur_xid  );

   //fill in cmd id VC_FILESYS_OPEN etc
   vchi_writebuf_uint32( &(msg->cmd_code), cmd_id );

   //we always have cmd_id, xid
   msg_len += 8;

   //return response code
   return (int) vchi_msg_queue( vc_filesys_client.open_handle, msg, (uint32_t)msg_len, VCHI_FLAGS_BLOCK_UNTIL_QUEUED, NULL );
}