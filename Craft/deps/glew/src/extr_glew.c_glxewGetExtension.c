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
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GLX_EXTENSIONS ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  _glewSearchExtension (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int _glewStrLen (int /*<<< orphan*/  const*) ; 
 scalar_t__ glXGetClientString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXGetCurrentDisplay () ; 

GLboolean glxewGetExtension (const char* name)
{    
  const GLubyte* start;
  const GLubyte* end;

  if (glXGetCurrentDisplay == NULL) return GL_FALSE;
  start = (const GLubyte*)glXGetClientString(glXGetCurrentDisplay(), GLX_EXTENSIONS);
  if (0 == start) return GL_FALSE;
  end = start + _glewStrLen(start);
  return _glewSearchExtension(name, start, end);
}