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
typedef  int /*<<< orphan*/  _GLFWcursor ;

/* Variables and functions */
 int GL_FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, int shape)
{
    // TODO
    fprintf(stderr, "_glfwPlatformCreateStandardCursor not implemented yet\n");
    return GL_FALSE;
}