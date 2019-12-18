#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * im; int /*<<< orphan*/  display; int /*<<< orphan*/  cursor; int /*<<< orphan*/  context; int /*<<< orphan*/  screen; int /*<<< orphan*/  root; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCloseIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XInitThreads () ; 
 int /*<<< orphan*/  XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenIM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSetLocaleModifiers (char*) ; 
 scalar_t__ XSupportsLocale () ; 
 int /*<<< orphan*/  XUniqueContext () ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInitContextAPI () ; 
 int /*<<< orphan*/  _glfwInitJoysticks () ; 
 int /*<<< orphan*/  _glfwInitTimer () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  createNULLCursor () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  hasUsableInputMethodStyle () ; 
 int /*<<< orphan*/  initExtensions () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int _glfwPlatformInit(void)
{
#if !defined(X_HAVE_UTF8_STRING)
    // HACK: If the current locale is C, apply the environment's locale
    //       This is done because the C locale breaks wide character input
    if (strcmp(setlocale(LC_CTYPE, NULL), "C") == 0)
        setlocale(LC_CTYPE, "");
#endif

    XInitThreads();

    _glfw.x11.display = XOpenDisplay(NULL);
    if (!_glfw.x11.display)
    {
        const char* display = getenv("DISPLAY");
        if (display)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: Failed to open display %s", display);
        }
        else
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: The DISPLAY environment variable is missing");
        }

        return GL_FALSE;
    }

    _glfw.x11.screen = DefaultScreen(_glfw.x11.display);
    _glfw.x11.root = RootWindow(_glfw.x11.display, _glfw.x11.screen);
    _glfw.x11.context = XUniqueContext();

    if (!initExtensions())
        return GL_FALSE;

    _glfw.x11.cursor = createNULLCursor();

    if (XSupportsLocale())
    {
        XSetLocaleModifiers("");

        _glfw.x11.im = XOpenIM(_glfw.x11.display, 0, NULL, NULL);
        if (_glfw.x11.im)
        {
            if (!hasUsableInputMethodStyle())
            {
                XCloseIM(_glfw.x11.im);
                _glfw.x11.im = NULL;
            }
        }
    }

    if (!_glfwInitContextAPI())
        return GL_FALSE;

    if (!_glfwInitJoysticks())
        return GL_FALSE;

    _glfwInitTimer();

    return GL_TRUE;
}