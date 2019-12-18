#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WNDPROC ;
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/  lpfnWndProc; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_CLASS_ALREADY_EXISTS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HWND_MESSAGE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  UnregisterClassA (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HWND winraw_create_window(WNDPROC wnd_proc)
{
   HWND wnd;
   WNDCLASSA wc = {0};

   wc.hInstance = GetModuleHandleA(NULL);

   if (!wc.hInstance)
   {
      RARCH_ERR("[WINRAW]: GetModuleHandleA failed with error %lu.\n", GetLastError());
      return NULL;
   }

   wc.lpfnWndProc   = wnd_proc;
   wc.lpszClassName = "winraw-input";
   if (!RegisterClassA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
   {
      RARCH_ERR("[WINRAW]: RegisterClassA failed with error %lu.\n", GetLastError());
      return NULL;
   }

   wnd = CreateWindowExA(0, wc.lpszClassName, NULL, 0, 0, 0, 0, 0,
         HWND_MESSAGE, NULL, NULL, NULL);
   if (!wnd)
   {
      RARCH_ERR("[WINRAW]: CreateWindowExA failed with error %lu.\n", GetLastError());
      goto error;
   }

   return wnd;

error:
   UnregisterClassA(wc.lpszClassName, NULL);
   return NULL;
}