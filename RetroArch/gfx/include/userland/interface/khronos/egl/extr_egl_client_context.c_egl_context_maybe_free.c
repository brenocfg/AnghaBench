#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ is_current; int /*<<< orphan*/  is_destroyed; } ;
typedef  TYPE_1__ EGL_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  egl_context_term (TYPE_1__*) ; 
 int /*<<< orphan*/  khrn_platform_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 

void egl_context_maybe_free(EGL_CONTEXT_T *context)
{
   vcos_assert(context);

   if (!context->is_destroyed)
      return;

   if (context->is_current)
      return;

   egl_context_term(context);
   khrn_platform_free(context);
}