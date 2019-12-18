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
struct TYPE_3__ {int rotation; } ;
typedef  TYPE_1__ gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  default_ortho ; 
 int /*<<< orphan*/  gl2_set_projection (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gl2_set_rotation(void *data, unsigned rotation)
{
   gl_t               *gl = (gl_t*)data;

   if (!gl)
      return;

   gl->rotation = 90 * rotation;
   gl2_set_projection(gl, &default_ortho, true);
}