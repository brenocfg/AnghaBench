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
typedef  TYPE_1__ gl1_t ;

/* Variables and functions */
 int /*<<< orphan*/  gl1_default_ortho ; 
 int /*<<< orphan*/  gl1_set_projection (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gl1_gfx_set_rotation(void *data,
      unsigned rotation)
{
   gl1_t *gl1 = (gl1_t*)data;

   if (!gl1)
      return;

   gl1->rotation = 90 * rotation;
   gl1_set_projection(gl1, &gl1_default_ortho, true);
}