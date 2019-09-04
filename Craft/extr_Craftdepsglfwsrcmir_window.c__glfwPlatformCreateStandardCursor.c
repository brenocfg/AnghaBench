#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * custom_cursor; int /*<<< orphan*/  conf; } ;
struct TYPE_5__ {TYPE_1__ mir; } ;
typedef  TYPE_2__ _GLFWcursor ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 char* getSystemCursorName (int) ; 
 int /*<<< orphan*/  mir_cursor_configuration_from_name (char const*) ; 

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, int shape)
{
    const char* cursor_name = getSystemCursorName(shape);

    if (cursor_name)
    {
        cursor->mir.conf          = mir_cursor_configuration_from_name(cursor_name);
        cursor->mir.custom_cursor = NULL;

        return GL_TRUE;
    }

    return GL_FALSE;
}