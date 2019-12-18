#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCSM_CACHE_TYPE_T ;
struct TYPE_9__ {int /*<<< orphan*/  vcsm_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/ * attribute_locations; int /*<<< orphan*/  program; } ;
struct TYPE_7__ {int /*<<< orphan*/ * attribute_locations; int /*<<< orphan*/  program; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  y_texture; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_EXTERNAL_OES ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCSM_CACHE_TYPE_HOST ; 
 int /*<<< orphan*/  fb_height ; 
 int /*<<< orphan*/  fb_name ; 
 int /*<<< orphan*/  fb_tex_name ; 
 int /*<<< orphan*/  fb_width ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFinish () ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quad_vbo ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_5__ vcsm_info ; 
 scalar_t__ vcsm_lock_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcsm_square_draw_pattern (unsigned char*) ; 
 TYPE_4__ vcsm_square_oes_shader ; 
 TYPE_2__ vcsm_square_shader ; 
 int /*<<< orphan*/  vcsm_unlock_ptr (unsigned char*) ; 

__attribute__((used)) static int vcsm_square_redraw(RASPITEX_STATE *raspitex_state)
{
    unsigned char *vcsm_buffer = NULL;
    VCSM_CACHE_TYPE_T cache_type;

    vcos_log_trace("%s", VCOS_FUNCTION);

    glClearColor(255, 0, 0, 255);

    GLCHK(glBindFramebuffer(GL_FRAMEBUFFER, fb_name));
    GLCHK(glViewport(0, 0, fb_width, fb_height));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Fill the viewport with the camFill the viewport with the camera image
    GLCHK(glUseProgram(vcsm_square_oes_shader.program));
    GLCHK(glActiveTexture(GL_TEXTURE0));
    GLCHK(glBindTexture(GL_TEXTURE_EXTERNAL_OES, raspitex_state->y_texture));
    GLCHK(glBindBuffer(GL_ARRAY_BUFFER, quad_vbo));
    GLCHK(glEnableVertexAttribArray(vcsm_square_oes_shader.attribute_locations[0]));
    GLCHK(glVertexAttribPointer(vcsm_square_oes_shader.attribute_locations[0], 2, GL_FLOAT, GL_FALSE, 0, 0));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    GLCHK(glFinish());

    // Make the buffer CPU addressable with host cache enabled
    vcsm_buffer = (unsigned char *) vcsm_lock_cache(vcsm_info.vcsm_handle, VCSM_CACHE_TYPE_HOST, &cache_type);
    if (! vcsm_buffer) {
        vcos_log_error("Failed to lock VCSM buffer for handle %d\n", vcsm_info.vcsm_handle);
        return -1;
    }
    vcos_log_trace("Locked vcsm handle %d at %p\n", vcsm_info.vcsm_handle, vcsm_buffer);

    vcsm_square_draw_pattern(vcsm_buffer);

    // Release the locked texture memory to flush the CPU cache and allow GPU
    // to read it
    vcsm_unlock_ptr(vcsm_buffer);

    // Enable default window surface
    GLCHK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    // Draw the modified texture buffer to the screen
    GLCHK(glViewport(raspitex_state->x, raspitex_state->y, raspitex_state->width, raspitex_state->height));
    GLCHK(glUseProgram(vcsm_square_shader.program));
    GLCHK(glActiveTexture(GL_TEXTURE0));
    GLCHK(glBindTexture(GL_TEXTURE_2D, fb_tex_name));
    GLCHK(glEnableVertexAttribArray(vcsm_square_shader.attribute_locations[0]));
    GLCHK(glVertexAttribPointer(vcsm_square_shader.attribute_locations[0], 2, GL_FLOAT, GL_FALSE, 0, 0));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6));

    GLCHK(glDisableVertexAttribArray(vcsm_square_shader.attribute_locations[0]));
    GLCHK(glUseProgram(0));

    return 0;
}