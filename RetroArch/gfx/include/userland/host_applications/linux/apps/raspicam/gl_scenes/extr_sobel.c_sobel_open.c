#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  update_y_texture; int /*<<< orphan*/  redraw; int /*<<< orphan*/  gl_init; } ;
struct TYPE_5__ {TYPE_1__ ops; } ;
typedef  TYPE_2__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  raspitexutil_update_y_texture ; 
 int /*<<< orphan*/  sobel_init ; 
 int /*<<< orphan*/  sobel_redraw ; 

int sobel_open(RASPITEX_STATE *state)
{
   state->ops.gl_init = sobel_init;
   state->ops.redraw = sobel_redraw;
   state->ops.update_y_texture = raspitexutil_update_y_texture;
   return 0;
}