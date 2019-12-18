#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ context_current_count; int connected; scalar_t__ inited; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* khrn_misc_try_unload_impl ) () ;} ;
typedef  TYPE_1__ KHRONOS_FUNC_TABLE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;
typedef  TYPE_2__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  KHRNMISCTRYUNLOAD_ID ; 
 int /*<<< orphan*/  RPC_CALL0_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_INT_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_library_get_connection () ; 
 int /*<<< orphan*/  khrn_misc_try_unload_impl ; 
 int /*<<< orphan*/  khronos_server_disconnect () ; 
 TYPE_1__* khronos_server_lock_func_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  khronos_server_unlock_func_table () ; 
 int /*<<< orphan*/  stub1 () ; 

void client_try_unload_server(CLIENT_PROCESS_STATE_T *process)
{
   if (/* some context is current */
      (process->context_current_count != 0) ||
      /* egl is initialised */
      process->inited) {
      return;
   }

   /*
      Prompt the server to unload Khronos VLL if it can,
      and wait until it is done
   */
#ifdef RPC_LIBRARY   //TODO: not thread safe
   if (process->connected) {
      const KHRONOS_FUNC_TABLE_T *func_table;
      func_table = khronos_server_lock_func_table(client_library_get_connection());
      if (func_table != NULL)
      {
         func_table->khrn_misc_try_unload_impl();
         khronos_server_disconnect();
      }
      khronos_server_unlock_func_table();

      process->connected = false;
   }
#else
   {
      CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
      RPC_INT_RES(RPC_CALL0_RES(khrn_misc_try_unload_impl, thread, KHRNMISCTRYUNLOAD_ID)); // return unimportant - read is just to cause blocking
   }
#endif
}