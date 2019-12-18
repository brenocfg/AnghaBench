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
struct TYPE_5__ {TYPE_1__* js; } ;
struct TYPE_6__ {TYPE_2__ linux_js; } ;
struct TYPE_4__ {int fd; int axisCount; int buttonCount; scalar_t__ present; void* buttons; void* axes; void* path; void* name; } ;

/* Variables and functions */
 int GLFW_JOYSTICK_1 ; 
 int GLFW_JOYSTICK_LAST ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  JSIOCGAXES ; 
 int /*<<< orphan*/  JSIOCGBUTTONS ; 
 int /*<<< orphan*/  JSIOCGNAME (int) ; 
 int /*<<< orphan*/  JSIOCGVERSION ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 TYPE_3__ _glfw ; 
 void* calloc (char,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,...) ; 
 int open (char const*,int) ; 
 scalar_t__ strcmp (void*,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void openJoystickDevice(const char* path)
{
#if defined(__linux__)
    char axisCount, buttonCount;
    char name[256];
    int joy, fd, version;

    for (joy = GLFW_JOYSTICK_1;  joy <= GLFW_JOYSTICK_LAST;  joy++)
    {
        if (!_glfw.linux_js.js[joy].present)
            continue;

        if (strcmp(_glfw.linux_js.js[joy].path, path) == 0)
            return;
    }

    for (joy = GLFW_JOYSTICK_1;  joy <= GLFW_JOYSTICK_LAST;  joy++)
    {
        if (!_glfw.linux_js.js[joy].present)
            break;
    }

    if (joy > GLFW_JOYSTICK_LAST)
        return;

    fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1)
        return;

    _glfw.linux_js.js[joy].fd = fd;

    // Verify that the joystick driver version is at least 1.0
    ioctl(fd, JSIOCGVERSION, &version);
    if (version < 0x010000)
    {
        // It's an old 0.x interface (we don't support it)
        close(fd);
        return;
    }

    if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0)
        strncpy(name, "Unknown", sizeof(name));

    _glfw.linux_js.js[joy].name = strdup(name);
    _glfw.linux_js.js[joy].path = strdup(path);

    ioctl(fd, JSIOCGAXES, &axisCount);
    _glfw.linux_js.js[joy].axisCount = (int) axisCount;

    ioctl(fd, JSIOCGBUTTONS, &buttonCount);
    _glfw.linux_js.js[joy].buttonCount = (int) buttonCount;

    _glfw.linux_js.js[joy].axes = calloc(axisCount, sizeof(float));
    _glfw.linux_js.js[joy].buttons = calloc(buttonCount, 1);

    _glfw.linux_js.js[joy].present = GL_TRUE;
#endif // __linux__
}