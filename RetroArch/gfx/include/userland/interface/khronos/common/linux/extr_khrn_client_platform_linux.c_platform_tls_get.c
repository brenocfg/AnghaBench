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
typedef  int /*<<< orphan*/  PLATFORM_TLS_T ;

/* Variables and functions */
 int /*<<< orphan*/  client_process_attach () ; 
 int /*<<< orphan*/  client_thread_attach () ; 
 int /*<<< orphan*/  client_thread_detach ; 
 int /*<<< orphan*/  client_tls ; 
 int process_attached ; 
 int /*<<< orphan*/  vc_vchi_khronos_init () ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 
 int /*<<< orphan*/  vcos_thread_at_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* vcos_tls_get (int /*<<< orphan*/ ) ; 

void *platform_tls_get(PLATFORM_TLS_T tls)
{
   void *ret;

   if (!process_attached)
      /* TODO: this isn't thread safe */
   {
      vcos_log_trace("Attaching process");
      client_process_attach();
      process_attached = true;
      tls = client_tls;

      vc_vchi_khronos_init();
   }

   ret = vcos_tls_get(tls);
   if (!ret)
   {
     /* The problem here is that on VCFW, the first notification we get that a thread
       * exists at all is when it calls an arbitrary EGL function. We need to detect this
       * case and initiliase the per-thread state.
       *
       * On Windows this gets done in DllMain.
       */
      client_thread_attach();
      vcos_thread_at_exit(client_thread_detach, NULL);
      ret = vcos_tls_get(tls);
   }
   return ret;
}