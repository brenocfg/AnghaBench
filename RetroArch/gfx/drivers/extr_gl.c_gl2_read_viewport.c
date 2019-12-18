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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  gl_t ;

/* Variables and functions */
 int gl2_renderchain_read_viewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool gl2_read_viewport(void *data, uint8_t *buffer, bool is_idle)
{
   gl_t *gl             = (gl_t*)data;

   if (!gl)
      return false;

   return gl2_renderchain_read_viewport(gl, buffer, is_idle);
}