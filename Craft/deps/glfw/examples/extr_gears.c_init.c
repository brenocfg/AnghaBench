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
 int /*<<< orphan*/  GL_AMBIENT_AND_DIFFUSE ; 
 int /*<<< orphan*/  GL_COMPILE ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_NORMALIZE ; 
 int /*<<< orphan*/  GL_POSITION ; 
 int /*<<< orphan*/  gear (float,float,float,int,float) ; 
 int /*<<< orphan*/  gear1 ; 
 int /*<<< orphan*/  gear2 ; 
 int /*<<< orphan*/  gear3 ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEndList () ; 
 int /*<<< orphan*/  glGenLists (int) ; 
 int /*<<< orphan*/  glLightfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glMaterialfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glNewList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init(void)
{
  static GLfloat pos[4] = {5.f, 5.f, 10.f, 0.f};
  static GLfloat red[4] = {0.8f, 0.1f, 0.f, 1.f};
  static GLfloat green[4] = {0.f, 0.8f, 0.2f, 1.f};
  static GLfloat blue[4] = {0.2f, 0.2f, 1.f, 1.f};

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  /* make the gears */
  gear1 = glGenLists(1);
  glNewList(gear1, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
  gear(1.f, 4.f, 1.f, 20, 0.7f);
  glEndList();

  gear2 = glGenLists(1);
  glNewList(gear2, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
  gear(0.5f, 2.f, 2.f, 10, 0.7f);
  glEndList();

  gear3 = glGenLists(1);
  glNewList(gear3, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
  gear(1.3f, 2.f, 0.5f, 10, 0.7f);
  glEndList();

  glEnable(GL_NORMALIZE);
}