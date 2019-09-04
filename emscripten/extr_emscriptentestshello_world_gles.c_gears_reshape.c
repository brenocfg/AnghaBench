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
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  ProjectionMatrix ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perspective (int /*<<< orphan*/ ,double,int,double,double) ; 

__attribute__((used)) static void
gears_reshape(int width, int height)
{
   /* Update the projection matrix */
   perspective(ProjectionMatrix, 60.0, width / (float)height, 1.0, 1024.0);

   /* Set the viewport */
   glViewport(0, 0, (GLint) width, (GLint) height);
}