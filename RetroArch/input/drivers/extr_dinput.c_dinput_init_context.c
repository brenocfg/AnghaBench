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

/* Variables and functions */
 int /*<<< orphan*/  DIRECTINPUT_VERSION ; 
 int /*<<< orphan*/  DirectInput8Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *****,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ **** IID_IDirectInput8 ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ g_dinput_ctx ; 

bool dinput_init_context(void)
{
   if (g_dinput_ctx)
      return true;

   /* Who said we shouldn't have same call signature in a COM API? <_< */
#ifdef __cplusplus
   if (!(SUCCEEDED(DirectInput8Create(
                  GetModuleHandle(NULL), DIRECTINPUT_VERSION,
                  IID_IDirectInput8,
                  (void**)&g_dinput_ctx, NULL))))
#else
      if (!(SUCCEEDED(DirectInput8Create(
                     GetModuleHandle(NULL), DIRECTINPUT_VERSION,
                     &IID_IDirectInput8,
                     (void**)&g_dinput_ctx, NULL))))
#endif
      goto error;

   return true;

error:
   RARCH_ERR("[DINPUT]: Failed to initialize DirectInput.\n");
   return false;
}