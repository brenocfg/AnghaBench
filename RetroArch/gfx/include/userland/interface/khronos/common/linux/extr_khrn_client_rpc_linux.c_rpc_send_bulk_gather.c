#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE () ; 
 int /*<<< orphan*/  check_workspace (int) ; 
 int /*<<< orphan*/  merge_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gather (void const*,void const*,int,int,int) ; 
 int /*<<< orphan*/  send_bulk (int /*<<< orphan*/ *,void const*,int) ; 
 void const* workspace ; 

void rpc_send_bulk_gather(CLIENT_THREAD_STATE_T *thread, const void *in, uint32_t len, int32_t stride, uint32_t n)
{
#if 1
   if (in && len) {
      //CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

      merge_flush(thread);

      if (len == stride) {
         /* hopefully should be the common case */
         send_bulk(thread, in, n * len);
      } else {
         check_workspace(n * len);
         rpc_gather(workspace, in, len, stride, n);
         send_bulk(thread, workspace, n * len);
      }
   }
#else
   UNREACHABLE();
#endif
}