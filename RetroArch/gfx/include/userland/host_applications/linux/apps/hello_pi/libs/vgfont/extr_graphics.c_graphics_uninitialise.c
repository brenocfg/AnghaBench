#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  disp; } ;

/* Variables and functions */
 int GRAPHICS_RESOURCE_HANDLE_TYPE_MAX ; 
 TYPE_1__ display ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglTerminate (int /*<<< orphan*/ ) ; 
 scalar_t__* gx_contexts ; 
 int /*<<< orphan*/  gx_log_cat ; 
 int /*<<< orphan*/  gx_priv_destroy () ; 
 int /*<<< orphan*/  gx_priv_font_term () ; 
 scalar_t__ inited ; 
 int /*<<< orphan*/  vcos_assert (scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ *) ; 

int32_t graphics_uninitialise( void )
{
   int i;
   vcos_assert(inited);

   gx_priv_font_term();

   for (i=0; i<GRAPHICS_RESOURCE_HANDLE_TYPE_MAX; i++)
      if (gx_contexts[i])
         eglDestroyContext(display.disp,gx_contexts[i]);

   eglTerminate(display.disp);
   gx_priv_destroy();
   vcos_log_unregister(&gx_log_cat);
   inited = 0;
   return 0;
}