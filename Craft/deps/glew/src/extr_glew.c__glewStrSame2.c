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
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ const GLubyte ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 

__attribute__((used)) static GLboolean _glewStrSame2 (GLubyte** a, GLuint* na, const GLubyte* b, GLuint nb)
{
  if(*na >= nb)
  {
    GLuint i=0;
    while (i < nb && (*a)+i != NULL && b+i != NULL && (*a)[i] == b[i]) i++;
    if(i == nb)
    {
      *a = *a + nb;
      *na = *na - nb;
      return GL_TRUE;
    }
  }
  return GL_FALSE;
}