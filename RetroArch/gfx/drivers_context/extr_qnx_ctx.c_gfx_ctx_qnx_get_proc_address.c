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
typedef  int /*<<< orphan*/  gfx_ctx_proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_get_proc_address (char const*) ; 

__attribute__((used)) static gfx_ctx_proc_t gfx_ctx_qnx_get_proc_address(const char *symbol)
{
#ifdef HAVE_EGL
   return egl_get_proc_address(symbol);
#endif
}