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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  open_handle; } ;
struct TYPE_5__ {scalar_t__ cmd_code; scalar_t__ xid; scalar_t__* params; } ;
typedef  TYPE_1__ FILESERV_MSG_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 scalar_t__ VCHI_MAX_MSG_SIZE ; 
 TYPE_4__ vc_filesys_client ; 
 scalar_t__ vchi_msg_queue (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_writebuf_uint32 (scalar_t__*,scalar_t__) ; 
 scalar_t__ vcos_verify (int) ; 

__attribute__((used)) static int vc_send_response( FILESERV_MSG_T* msg, uint32_t retval, uint32_t nbytes )
{
   int success = -1;
   //convert all to over the wire values
   vchi_writebuf_uint32(&msg->cmd_code, retval);
   vchi_writebuf_uint32(&msg->xid, msg->xid);
   vchi_writebuf_uint32(&msg->params[0], msg->params[0]);
   vchi_writebuf_uint32(&msg->params[1], msg->params[1]);
   vchi_writebuf_uint32(&msg->params[2], msg->params[2]);
   vchi_writebuf_uint32(&msg->params[3], msg->params[3]);

   //start with 8 because always xid and retval
   nbytes += 8;

   if(vcos_verify(nbytes <= VCHI_MAX_MSG_SIZE))
      success = (int) vchi_msg_queue( vc_filesys_client.open_handle, msg, nbytes, VCHI_FLAGS_BLOCK_UNTIL_QUEUED, NULL );

   return success;
}