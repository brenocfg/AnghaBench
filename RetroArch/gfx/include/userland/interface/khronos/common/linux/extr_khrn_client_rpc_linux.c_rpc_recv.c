#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ VCHIQ_HEADER_T ;
typedef  int RPC_RECV_FLAG_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int RPC_RECV_FLAG_BULK ; 
 int RPC_RECV_FLAG_BULK_SCATTER ; 
 int RPC_RECV_FLAG_CTRL ; 
 int RPC_RECV_FLAG_LEN ; 
 int RPC_RECV_FLAG_RES ; 
 int /*<<< orphan*/  check_workspace (int) ; 
 int /*<<< orphan*/  get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  merge_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_bulk (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  rpc_scatter (void*,int,int,int,int,int,void*) ; 
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* vchiu_queue_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 void* workspace ; 

uint32_t rpc_recv(CLIENT_THREAD_STATE_T *thread, void *out, uint32_t *len_io, RPC_RECV_FLAG_T flags)
{
   uint32_t res = 0;
   uint32_t len;
   bool recv_ctrl;

   if (!len_io) { len_io = &len; }

   recv_ctrl = flags & (RPC_RECV_FLAG_RES | RPC_RECV_FLAG_CTRL | RPC_RECV_FLAG_LEN); /* do we want to receive anything in the control channel at all? */
   vcos_assert(recv_ctrl || (flags & RPC_RECV_FLAG_BULK)); /* must receive something... */
   vcos_assert(!(flags & RPC_RECV_FLAG_CTRL) || !(flags & RPC_RECV_FLAG_BULK)); /* can't receive user data over both bulk and control... */

   if (recv_ctrl || len_io[0]) { /* do nothing if we're just receiving bulk of length 0 */
      merge_flush(thread);

      if (recv_ctrl) {
         VCHIQ_HEADER_T *header = vchiu_queue_pop(get_queue(thread));
         uint8_t *ctrl = (uint8_t *)header->data;
         vcos_assert(header->size >= (!!(flags & RPC_RECV_FLAG_LEN)*4 + !!(flags & RPC_RECV_FLAG_RES)*4) );
         if (flags & RPC_RECV_FLAG_LEN) {
            len_io[0] = *((uint32_t *)ctrl);
            ctrl += 4;
         }
         if (flags & RPC_RECV_FLAG_RES) {
            res = *((uint32_t *)ctrl);
            ctrl += 4;
         }
         if (flags & RPC_RECV_FLAG_CTRL) {
            memcpy(out, ctrl, len_io[0]);
            ctrl += len_io[0];
         }
         vcos_assert(ctrl == ((uint8_t *)header->data + header->size));
         vchiq_release_message(get_handle(thread), header);
      }

      if ((flags & RPC_RECV_FLAG_BULK) && len_io[0]) {
         if (flags & RPC_RECV_FLAG_BULK_SCATTER) {
            if ((len_io[0] == len_io[1]) && !len_io[3] && !len_io[4]) {
               /* hopefully should be the common case */
               recv_bulk(thread, out, len_io[2] * len_io[0]);
            } else {
               check_workspace(len_io[2] * len_io[0]);
               recv_bulk(thread, workspace, len_io[2] * len_io[0]);
               rpc_scatter(out, len_io[0], len_io[1], len_io[2], len_io[3], len_io[4], workspace);
            }
         } else {
            recv_bulk(thread, out, len_io[0]);
         }
      }
   }

   return res;
}