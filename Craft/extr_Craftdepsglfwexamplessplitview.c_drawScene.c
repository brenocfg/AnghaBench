#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DIFFUSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_SHININESS ; 
 int /*<<< orphan*/  GL_SPECULAR ; 
 int /*<<< orphan*/  drawTorus () ; 
 int /*<<< orphan*/  glColor4fv (float const*) ; 
 int /*<<< orphan*/  glMaterialf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const) ; 
 int /*<<< orphan*/  glMaterialfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glRotatef (float,float,float,float) ; 
 scalar_t__ rot_x ; 
 scalar_t__ rot_y ; 
 scalar_t__ rot_z ; 

__attribute__((used)) static void drawScene(void)
{
    const GLfloat model_diffuse[4]  = {1.0f, 0.8f, 0.8f, 1.0f};
    const GLfloat model_specular[4] = {0.6f, 0.6f, 0.6f, 1.0f};
    const GLfloat model_shininess   = 20.0f;

    glPushMatrix();

    // Rotate the object
    glRotatef((GLfloat) rot_x * 0.5f, 1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat) rot_y * 0.5f, 0.0f, 1.0f, 0.0f);
    glRotatef((GLfloat) rot_z * 0.5f, 0.0f, 0.0f, 1.0f);

    // Set model color (used for orthogonal views, lighting disabled)
    glColor4fv(model_diffuse);

    // Set model material (used for perspective view, lighting enabled)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, model_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, model_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, model_shininess);

    // Draw torus
    drawTorus();

    glPopMatrix();
}