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
struct TYPE_3__ {size_t scratch_vbo_index; int /*<<< orphan*/ * scratch_vbos; } ;
typedef  TYPE_1__ gl_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 size_t GL_CORE_NUM_VBOS ; 
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,size_t,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 

void gl_core_bind_scratch_vbo(gl_core_t *gl, const void *data, size_t size)
{
   if (!gl->scratch_vbos[gl->scratch_vbo_index])
      glGenBuffers(1, &gl->scratch_vbos[gl->scratch_vbo_index]);
   glBindBuffer(GL_ARRAY_BUFFER, gl->scratch_vbos[gl->scratch_vbo_index]);
   glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
   gl->scratch_vbo_index++;
   if (gl->scratch_vbo_index >= GL_CORE_NUM_VBOS)
      gl->scratch_vbo_index = 0;
}