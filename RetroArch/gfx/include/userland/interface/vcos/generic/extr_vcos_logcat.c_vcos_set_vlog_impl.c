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
typedef  int /*<<< orphan*/ * VCOS_VLOG_IMPL_FUNC_T ;

/* Variables and functions */
 int /*<<< orphan*/ * vcos_vlog_default_impl ; 
 int /*<<< orphan*/ * vcos_vlog_impl_func ; 

void vcos_set_vlog_impl( VCOS_VLOG_IMPL_FUNC_T vlog_impl_func )
{
   if ( vlog_impl_func == NULL )
   {
      vcos_vlog_impl_func = vcos_vlog_default_impl;
   }
   else
   {
      vcos_vlog_impl_func = vlog_impl_func;
   }
}