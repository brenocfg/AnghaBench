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
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_ELAPSED_TIME ; 
 double angle ; 
 double glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutPostRedisplay () ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void
gears_idle(void)
{
   static int frames = 0;
   static double tRot0 = -1.0, tRate0 = -1.0;
   double dt, t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

   if (tRot0 < 0.0)
      tRot0 = t;
   dt = t - tRot0;
   tRot0 = t;

   /* advance rotation for next frame */
   angle += 70.0 * dt;  /* 70 degrees per second */
   if (angle > 3600.0)
      angle -= 3600.0;

#ifdef TEST_MEMORYPROFILER_ALLOCATIONS_MAP
   // This file is used to test --memoryprofiler linker flag, in which case
   // add some allocation noise.
   static void *allocatedPtr = 0;
   free(allocatedPtr);
   allocatedPtr = malloc(rand() % 10485760);
#endif

   glutPostRedisplay();
   frames++;

   if (tRate0 < 0.0)
      tRate0 = t;
   if (t - tRate0 >= 5.0) {
      GLfloat seconds = t - tRate0;
      GLfloat fps = frames / seconds;
      printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, seconds,
            fps);
      tRate0 = t;
      frames = 0;
#ifdef LONGTEST
      static int runs = 0;
      runs++;
      if (runs == 4) {
        int result = fps;
#ifdef TEST_MEMORYPROFILER_ALLOCATIONS_MAP
        result = 0;
#endif
        REPORT_RESULT(result);
      }
#endif
   }
}