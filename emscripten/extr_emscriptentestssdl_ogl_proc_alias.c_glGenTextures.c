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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  true_glGenTextures (int,int /*<<< orphan*/ *) ; 

void glGenTextures(GLsizei n, GLuint *textures) {
  printf("num? %d\n", n);
  true_glGenTextures(n + 1, textures); // correct the error, ensures we are gone through
}