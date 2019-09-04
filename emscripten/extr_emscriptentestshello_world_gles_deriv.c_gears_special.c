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

/* Variables and functions */
#define  GLUT_KEY_DOWN 131 
#define  GLUT_KEY_LEFT 130 
#define  GLUT_KEY_RIGHT 129 
#define  GLUT_KEY_UP 128 
 double* view_rot ; 

__attribute__((used)) static void
gears_special(int special, int crap, int morecrap)
{
   switch (special) {
      case GLUT_KEY_LEFT:
         view_rot[1] += 5.0;
         break;
      case GLUT_KEY_RIGHT:
         view_rot[1] -= 5.0;
         break;
      case GLUT_KEY_UP:
         view_rot[0] += 5.0;
         break;
      case GLUT_KEY_DOWN:
         view_rot[0] -= 5.0;
         break;
   }
}