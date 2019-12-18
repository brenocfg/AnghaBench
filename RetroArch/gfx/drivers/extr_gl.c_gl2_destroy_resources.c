#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* conv_buffer; struct TYPE_4__* empty_buf; } ;
typedef  TYPE_1__ gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_query_core_context_unset () ; 
 int gl_shared_context_use ; 

__attribute__((used)) static void gl2_destroy_resources(gl_t *gl)
{
   if (gl)
   {
      if (gl->empty_buf)
         free(gl->empty_buf);
      if (gl->conv_buffer)
         free(gl->conv_buffer);
      free(gl);
   }

   gl_shared_context_use   = false;

   gl_query_core_context_unset();
}