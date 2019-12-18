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
typedef  scalar_t__ mat4x4 ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_CCW ; 
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_EXP ; 
 int /*<<< orphan*/  GL_FOG ; 
 int /*<<< orphan*/  GL_FOG_COLOR ; 
 int /*<<< orphan*/  GL_FOG_DENSITY ; 
 int /*<<< orphan*/  GL_FOG_MODE ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_TRUE ; 
 double M_PI ; 
 int /*<<< orphan*/  aspect_ratio ; 
 double cos (double) ; 
 int /*<<< orphan*/  draw_floor () ; 
 int /*<<< orphan*/  draw_fountain () ; 
 int /*<<< orphan*/  draw_particles (int /*<<< orphan*/ *,double,float) ; 
 int /*<<< orphan*/  fog_color ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFogf (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glFogfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFogi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFrontFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glLoadMatrixf (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glRotated (double,double,double,double) ; 
 int /*<<< orphan*/  glTranslated (double,double,double) ; 
 int /*<<< orphan*/  mat4x4_perspective (scalar_t__,float,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  setup_lights () ; 
 double sin (double) ; 

__attribute__((used)) static void draw_scene(GLFWwindow* window, double t)
{
    double xpos, ypos, zpos, angle_x, angle_y, angle_z;
    static double t_old = 0.0;
    float dt;
    mat4x4 projection;

    // Calculate frame-to-frame delta time
    dt = (float) (t - t_old);
    t_old = t;

    mat4x4_perspective(projection,
                       65.f * (float) M_PI / 180.f,
                       aspect_ratio,
                       1.0, 60.0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((const GLfloat*) projection);

    // Setup camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate camera
    angle_x = 90.0 - 10.0;
    angle_y = 10.0 * sin(0.3 * t);
    angle_z = 10.0 * t;
    glRotated(-angle_x, 1.0, 0.0, 0.0);
    glRotated(-angle_y, 0.0, 1.0, 0.0);
    glRotated(-angle_z, 0.0, 0.0, 1.0);

    // Translate camera
    xpos =  15.0 * sin((M_PI / 180.0) * angle_z) +
             2.0 * sin((M_PI / 180.0) * 3.1 * t);
    ypos = -15.0 * cos((M_PI / 180.0) * angle_z) +
             2.0 * cos((M_PI / 180.0) * 2.9 * t);
    zpos = 4.0 + 2.0 * cos((M_PI / 180.0) * 4.9 * t);
    glTranslated(-xpos, -ypos, -zpos);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    setup_lights();
    glEnable(GL_LIGHTING);

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, 0.05f);
    glFogfv(GL_FOG_COLOR, fog_color);

    draw_floor();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    draw_fountain();

    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);

    // Particles must be drawn after all solid objects have been drawn
    draw_particles(window, t, dt);

    // Z-buffer not needed anymore
    glDisable(GL_DEPTH_TEST);
}