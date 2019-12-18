#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_5__ {int fd; int axisCount; int buttonCount; void* buttons; void* axes; void* path; void* name; int /*<<< orphan*/  present; } ;
typedef  TYPE_2__ _GLFWjoystickLinux ;
struct TYPE_4__ {TYPE_2__* js; } ;
struct TYPE_6__ {TYPE_1__ linux_js; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CONNECTED ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int GLFW_JOYSTICK_1 ; 
 int GLFW_JOYSTICK_LAST ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  JSIOCGAXES ; 
 int /*<<< orphan*/  JSIOCGBUTTONS ; 
 int /*<<< orphan*/  JSIOCGNAME (int) ; 
 int /*<<< orphan*/  JSIOCGVERSION ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputJoystickChange (int,int /*<<< orphan*/ ) ; 
 void* calloc (char,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int open (char const*,int) ; 
 scalar_t__ strcmp (void*,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static GLFWbool openJoystickDevice(const char* path)
{
    char axisCount, buttonCount;
    char name[256] = "";
    int joy, fd, version;
    _GLFWjoystickLinux* js;

    for (joy = GLFW_JOYSTICK_1;  joy <= GLFW_JOYSTICK_LAST;  joy++)
    {
        if (!_glfw.linux_js.js[joy].present)
            continue;

        if (strcmp(_glfw.linux_js.js[joy].path, path) == 0)
            return GLFW_FALSE;
    }

    for (joy = GLFW_JOYSTICK_1;  joy <= GLFW_JOYSTICK_LAST;  joy++)
    {
        if (!_glfw.linux_js.js[joy].present)
            break;
    }

    if (joy > GLFW_JOYSTICK_LAST)
        return GLFW_FALSE;

    fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1)
        return GLFW_FALSE;

    // Verify that the joystick driver version is at least 1.0
    ioctl(fd, JSIOCGVERSION, &version);
    if (version < 0x010000)
    {
        // It's an old 0.x interface (we don't support it)
        close(fd);
        return GLFW_FALSE;
    }

    if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0)
        strncpy(name, "Unknown", sizeof(name));

    js = _glfw.linux_js.js + joy;
    js->present = GLFW_TRUE;
    js->name = strdup(name);
    js->path = strdup(path);
    js->fd = fd;

    ioctl(fd, JSIOCGAXES, &axisCount);
    js->axisCount = (int) axisCount;
    js->axes = calloc(axisCount, sizeof(float));

    ioctl(fd, JSIOCGBUTTONS, &buttonCount);
    js->buttonCount = (int) buttonCount;
    js->buttons = calloc(buttonCount, 1);

    _glfwInputJoystickChange(joy, GLFW_CONNECTED);
    return GLFW_TRUE;
}