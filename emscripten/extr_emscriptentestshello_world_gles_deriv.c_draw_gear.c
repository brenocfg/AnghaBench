#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gear {int nstrips; TYPE_1__* strips; int /*<<< orphan*/  vbo; } ;
typedef  int /*<<< orphan*/  normal_matrix ;
typedef  int /*<<< orphan*/  model_view_projection ;
typedef  int /*<<< orphan*/  model_view ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  first; } ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int M_PI ; 
 int /*<<< orphan*/  MaterialColor_location ; 
 int /*<<< orphan*/  ModelViewProjectionMatrix_location ; 
 int /*<<< orphan*/  NormalMatrix_location ; 
 int* ProjectionMatrix ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int,int const*) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  invert (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  multiply (int*,int*) ; 
 int /*<<< orphan*/  rotate (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  translate (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transpose (int*) ; 

__attribute__((used)) static void
draw_gear(struct gear *gear, GLfloat *transform,
      GLfloat x, GLfloat y, GLfloat angle, const GLfloat color[4])
{
   GLfloat model_view[16];
   GLfloat normal_matrix[16];
   GLfloat model_view_projection[16];

   /* Translate and rotate the gear */
   memcpy(model_view, transform, sizeof (model_view));
   translate(model_view, x, y, 0);
   rotate(model_view, 2 * M_PI * angle / 360.0, 0, 0, 1);

   /* Create and set the ModelViewProjectionMatrix */
   memcpy(model_view_projection, ProjectionMatrix, sizeof(model_view_projection));
   multiply(model_view_projection, model_view);

   glUniformMatrix4fv(ModelViewProjectionMatrix_location, 1, GL_FALSE,
                      model_view_projection);

   /* 
    * Create and set the NormalMatrix. It's the inverse transpose of the
    * ModelView matrix.
    */
   memcpy(normal_matrix, model_view, sizeof (normal_matrix));
   invert(normal_matrix);
   transpose(normal_matrix);
   glUniformMatrix4fv(NormalMatrix_location, 1, GL_FALSE, normal_matrix);

   /* Set the gear color */
   glUniform4fv(MaterialColor_location, 1, color);

   /* Set the vertex buffer object to use */
   glBindBuffer(GL_ARRAY_BUFFER, gear->vbo);

   /* Set up the position of the attributes in the vertex buffer object */
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
         6 * sizeof(GLfloat), NULL);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
         6 * sizeof(GLfloat), (GLfloat *) 0 + 3);

   /* Enable the attributes */
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);

   /* Draw the triangle strips that comprise the gear */
   int n;
   for (n = 0; n < gear->nstrips; n++)
      glDrawArrays(GL_TRIANGLE_STRIP, gear->strips[n].first, gear->strips[n].count);

   /* Disable the attributes */
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(0);
}