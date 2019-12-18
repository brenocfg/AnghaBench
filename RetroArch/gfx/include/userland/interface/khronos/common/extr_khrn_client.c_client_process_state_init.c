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
struct TYPE_6__ {int /*<<< orphan*/  make_current_func; } ;
struct TYPE_5__ {int inited; int next_surface; int next_context; int next_sync; int next_global_image_egl_image; int perf_monitor_inited; int connected; TYPE_2__ khrn_connection; int /*<<< orphan*/  global_image_egl_images; int /*<<< orphan*/  windows; int /*<<< orphan*/  surfaces; int /*<<< orphan*/  contexts; int /*<<< orphan*/  syncs; } ;
typedef  TYPE_1__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_CALL0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_library_send_make_current ; 
 int /*<<< orphan*/  egl_config_install_configs (int) ; 
 int /*<<< orphan*/  khrn_global_image_map_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  khrn_misc_startup_impl ; 
 int /*<<< orphan*/  khrn_pointer_map_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  khrn_pointer_map_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khronos_server_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  khronos_server_lock_func_table (TYPE_2__*) ; 
 int /*<<< orphan*/  khronos_server_unlock_func_table () ; 
 int /*<<< orphan*/  no_id ; 

bool client_process_state_init(CLIENT_PROCESS_STATE_T *process)
{
   if (!process->inited) {
      if (!khrn_pointer_map_init(&process->contexts, 64))
         return false;

      if (!khrn_pointer_map_init(&process->surfaces, 64))
      {
         khrn_pointer_map_term(&process->contexts);
         return false;
      }
      if (!khrn_pointer_map_init(&process->windows, 64))
      {
         khrn_pointer_map_term(&process->contexts);
         khrn_pointer_map_term(&process->surfaces);
         return false;
      }

#if EGL_KHR_sync
      if (!khrn_pointer_map_init(&process->syncs, 64))
      {
         khrn_pointer_map_term(&process->contexts);
         khrn_pointer_map_term(&process->surfaces);
         khrn_pointer_map_term(&process->windows);
         return false;
      }
#endif
#if EGL_BRCM_global_image && EGL_KHR_image
      khrn_global_image_map_init(&process->global_image_egl_images, 8);
#endif
      process->next_surface = 1;
      process->next_context = 1;
#if EGL_KHR_sync
      process->next_sync = 0x80000001;
#endif
#if EGL_BRCM_global_image && EGL_KHR_image
      process->next_global_image_egl_image = 1 << 31;
#endif

#if EGL_BRCM_perf_monitor
      process->perf_monitor_inited = false;
#endif

#ifdef RPC_LIBRARY
      if (!process->connected) {
         process->khrn_connection.make_current_func = client_library_send_make_current;
         khronos_server_lock_func_table(&process->khrn_connection);
         khronos_server_connect(&process->khrn_connection);
         khronos_server_unlock_func_table();
         RPC_CALL0(khrn_misc_startup_impl, NULL, no_id);

         process->connected = true;
      }
#endif

      process->inited = true;
   }

#ifndef ABSTRACT_PLATFORM
#if defined(ANDROID) && !defined (ANDROID_HWCOMPOSER)
   egl_config_install_configs(1); // T-format configs
#else
   egl_config_install_configs(0); // RSO configs
#endif
#endif

   return true;
}