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
typedef  void dispserv_win32_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/ **** CLSID_TaskbarList ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *****,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *****,void**) ; 
 int /*<<< orphan*/ **** IID_ITaskbarList3 ; 
 int /*<<< orphan*/  ITaskbarList3_HrInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * g_taskbarList ; 

__attribute__((used)) static void* win32_display_server_init(void)
{
   HRESULT hr;
   dispserv_win32_t *dispserv = (dispserv_win32_t*)calloc(1, sizeof(*dispserv));

   (void)hr;

   if (!dispserv)
      return NULL;

#ifdef HAS_TASKBAR_EXT
#ifdef __cplusplus
   /* When compiling in C++ mode, GUIDs are references instead of pointers */
   hr = CoCreateInstance(CLSID_TaskbarList, NULL,
         CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&g_taskbarList);
#else
   /* Mingw GUIDs are pointers instead of references since we're in C mode */
   hr = CoCreateInstance(&CLSID_TaskbarList, NULL,
         CLSCTX_INPROC_SERVER, &IID_ITaskbarList3, (void**)&g_taskbarList);
#endif

   if (SUCCEEDED(hr))
   {
      hr = ITaskbarList3_HrInit(g_taskbarList);

      if (!SUCCEEDED(hr))
         RARCH_ERR("[dispserv]: HrInit of ITaskbarList3 failed.\n");
   }
   else
   {
      g_taskbarList = NULL;
      RARCH_ERR("[dispserv]: CoCreateInstance of ITaskbarList3 failed.\n");
   }
#endif

   return dispserv;
}