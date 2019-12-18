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
struct TYPE_4__ {int /*<<< orphan*/  update_texture; int /*<<< orphan*/  gl_term; int /*<<< orphan*/  redraw; int /*<<< orphan*/  update_model; int /*<<< orphan*/  gl_init; } ;
struct TYPE_5__ {TYPE_1__ ops; } ;
typedef  TYPE_2__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  raspitexutil_update_texture ; 
 int /*<<< orphan*/  teapot_gl_init ; 
 int /*<<< orphan*/  teapot_gl_term ; 
 int /*<<< orphan*/  teapot_redraw ; 
 int /*<<< orphan*/  teapot_update_model ; 

int teapot_open(RASPITEX_STATE *raspitex_state)
{
   raspitex_state->ops.gl_init = teapot_gl_init;
   raspitex_state->ops.update_model = teapot_update_model;
   raspitex_state->ops.redraw = teapot_redraw;
   raspitex_state->ops.gl_term = teapot_gl_term;
   raspitex_state->ops.update_texture = raspitexutil_update_texture;
   return 0;
}