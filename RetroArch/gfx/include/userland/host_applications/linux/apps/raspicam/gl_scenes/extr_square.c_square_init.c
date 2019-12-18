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
typedef  int /*<<< orphan*/  RASPITEX_STATE ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 float angle ; 
 scalar_t__ anim_step ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearDepthf (int) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int raspitexutil_gl_init_1_0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int square_init(RASPITEX_STATE *state)
{
   int rc = raspitexutil_gl_init_1_0(state);

   if (rc != 0)
      goto end;

   angle = 0.0f;
   anim_step = 0;

   glClearColor(0, 0, 0, 0);
   glClearDepthf(1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

end:
   return rc;
}