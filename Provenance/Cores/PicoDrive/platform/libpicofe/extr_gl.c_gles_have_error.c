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
typedef  scalar_t__ EGLint ;

/* Variables and functions */
 scalar_t__ EGL_SUCCESS ; 
 scalar_t__ eglGetError () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int gles_have_error(const char *name)
{
	EGLint e = eglGetError();
	if (e != EGL_SUCCESS) {
		fprintf(stderr, "%s %x\n", name, e);
		return 1;
	}
	return 0;
}