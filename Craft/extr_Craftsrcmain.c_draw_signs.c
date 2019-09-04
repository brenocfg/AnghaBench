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
struct TYPE_3__ {int sign_faces; int /*<<< orphan*/  sign_buffer; } ;
typedef  TYPE_1__ Chunk ;
typedef  int /*<<< orphan*/  Attrib ;

/* Variables and functions */
 int /*<<< orphan*/  GL_POLYGON_OFFSET_FILL ; 
 int /*<<< orphan*/  draw_triangles_3d_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPolygonOffset (int,int) ; 

void draw_signs(Attrib *attrib, Chunk *chunk) {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-8, -1024);
    draw_triangles_3d_text(attrib, chunk->sign_buffer, chunk->sign_faces * 6);
    glDisable(GL_POLYGON_OFFSET_FILL);
}