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
typedef  enum gfx_ctx_api { ____Placeholder_gfx_ctx_api } gfx_ctx_api ;

/* Variables and functions */
 int win32_gdi_api ; 
 unsigned int win32_gdi_major ; 
 unsigned int win32_gdi_minor ; 

__attribute__((used)) static bool gfx_ctx_gdi_bind_api(void *data,
      enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   (void)data;

   win32_gdi_major = major;
   win32_gdi_minor = minor;
   win32_gdi_api   = api;

   return true;
}