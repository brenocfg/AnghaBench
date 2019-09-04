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
typedef  int /*<<< orphan*/  tmp ;
typedef  int GLfloat ;

/* Variables and functions */
 int M_PI ; 
 int /*<<< orphan*/  identity (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sincos (int,double*,double*) ; 

void perspective(GLfloat *m, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
   GLfloat tmp[16];
   identity(tmp);

   double sine, cosine, cotangent, deltaZ;
   GLfloat radians = fovy / 2 * M_PI / 180;

   deltaZ = zFar - zNear;
   sincos(radians, &sine, &cosine);

   if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
      return;

   cotangent = cosine / sine;

   tmp[0] = cotangent / aspect;
   tmp[5] = cotangent;
   tmp[10] = -(zFar + zNear) / deltaZ;
   tmp[11] = -1;
   tmp[14] = -2 * zNear * zFar / deltaZ;
   tmp[15] = 0;

   memcpy(m, tmp, sizeof(tmp));
}