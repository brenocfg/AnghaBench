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
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  raspitexutil_update_y_texture ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcsm_square_init ; 
 int /*<<< orphan*/  vcsm_square_redraw ; 
 int /*<<< orphan*/  vcsm_square_redraw_readpixels ; 

int vcsm_square_open(RASPITEX_STATE *raspitex_state)
{
    vcos_log_trace("%s", VCOS_FUNCTION);

    raspitex_state->ops.gl_init = vcsm_square_init;
#ifdef USE_READPIXELS
    raspitex_state->ops.redraw = vcsm_square_redraw_readpixels;
#else
    raspitex_state->ops.redraw = vcsm_square_redraw;
#endif /* USE_READPIXELS */
    raspitex_state->ops.update_y_texture = raspitexutil_update_y_texture;
    return 0;
}