#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_12__ {int vertices; float* vertex; int /*<<< orphan*/  tex_coord; int /*<<< orphan*/  color; } ;
typedef  TYPE_4__ video_coords_t ;
struct TYPE_13__ {TYPE_3__* gl; TYPE_1__* atlas; } ;
typedef  TYPE_5__ gl1_raster_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_2__ mvp; } ;
struct TYPE_9__ {int dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_TEXTURE_COORD_ARRAY ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  gl1_raster_font_upload_atlas (TYPE_5__*) ; 
 int /*<<< orphan*/  glColorPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glLoadMatrixf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glTexCoordPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 float* vertices3 ; 

__attribute__((used)) static void gl1_raster_font_draw_vertices(gl1_raster_t *font,
      const video_coords_t *coords,
      video_frame_info_t *video_info)
{
   if (font->atlas->dirty)
   {
      gl1_raster_font_upload_atlas(font);
      font->atlas->dirty   = false;
   }

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadMatrixf(font->gl->mvp.data);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);

#ifdef VITA
   if (vertices3)
      free(vertices3);
   vertices3 = (float*)malloc(sizeof(float) * 3 * coords->vertices);
   int i;
   for (i = 0; i < coords->vertices; i++) {
      memcpy(&vertices3[i*3], &coords->vertex[i*2], sizeof(float) * 2);
      vertices3[i*3] -= 0.5f;
      vertices3[i*3+2] = 0.0f;
   }
   glVertexPointer(3, GL_FLOAT, 0, vertices3);   
#else
   glVertexPointer(2, GL_FLOAT, 0, coords->vertex);
#endif

   glColorPointer(4, GL_FLOAT, 0, coords->color);
   glTexCoordPointer(2, GL_FLOAT, 0, coords->tex_coord);

   glDrawArrays(GL_TRIANGLES, 0, coords->vertices);

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);

   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
}