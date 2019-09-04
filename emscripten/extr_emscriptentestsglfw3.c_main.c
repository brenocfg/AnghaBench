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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CLIENT_API ; 
 int /*<<< orphan*/  GLFW_CURSOR ; 
 scalar_t__ GLFW_CURSOR_NORMAL ; 
 int /*<<< orphan*/  GLFW_KEY_A ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errorcb ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwDefaultWindowHints () ; 
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwExtensionSupported (char*) ; 
 int /*<<< orphan*/ * glfwGetCurrentContext () ; 
 int /*<<< orphan*/  glfwGetCursorPos (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwGetMonitorName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetMonitorPhysicalSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetMonitorPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ ** glfwGetMonitors (int*) ; 
 int /*<<< orphan*/  glfwGetMouseButton (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/ * glfwGetProcAddress (char*) ; 
 int /*<<< orphan*/  glfwGetTime () ; 
 int /*<<< orphan*/  glfwGetVersion (int*,int*,int*) ; 
 int /*<<< orphan*/  glfwGetVersionString () ; 
 scalar_t__ glfwGetWindowAttrib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 char* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetCharCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCursorEnterCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCursorPosCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMonitorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetScrollCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowCloseCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowFocusCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowIconifyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowPosCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  glfwSetWindowSize (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  glfwSetWindowSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowTitle (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glfwSetWindowUserPointer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,scalar_t__) ; 
 int glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  monitcb ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcharcb ; 
 int /*<<< orphan*/  wcloscb ; 
 int /*<<< orphan*/  wcurecb ; 
 int /*<<< orphan*/  wcurpcb ; 
 int /*<<< orphan*/  wfocucb ; 
 int /*<<< orphan*/  wfsizcb ; 
 int /*<<< orphan*/  wiconcb ; 
 int /*<<< orphan*/  wkeypcb ; 
 int /*<<< orphan*/  wmbutcb ; 
 int /*<<< orphan*/  wposicb ; 
 int /*<<< orphan*/  wrfrscb ; 
 int /*<<< orphan*/  wscrocb ; 
 int /*<<< orphan*/  wsizecb ; 

int main()
{
    GLFWwindow *window;
    char *userptr = "userptr";

    glfwSetErrorCallback(errorcb);
    assert(glfwInit() == GL_TRUE);
    assert(!strcmp(glfwGetVersionString(), "3.2.1 JS WebGL Emscripten"));
    assert(glfwGetCurrentContext() == NULL);

    {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        assert(major == 3);
        assert(minor == 2);
        assert(rev == 1);
    }

    {
        int count, x, y, w, h;
        GLFWmonitor **monitors = glfwGetMonitors(&count);
        assert(count == 1);
        for (int i = 0; i < count; ++i) {
            assert(monitors[i] != NULL);
        }

        assert(glfwGetPrimaryMonitor() != NULL);
        glfwGetMonitorPos(monitors[0], &x, &y);
        glfwGetMonitorPhysicalSize(monitors[0], &w, &h);
        assert(glfwGetMonitorName(monitors[0]) != NULL);
        glfwSetMonitorCallback(monitcb);

        // XXX: not implemented
        // assert(glfwGetVideoModes(monitors[0], &count) != NULL);
        // assert(glfwGetVideoMode(monitors[0]) != NULL);
        // glfwSetGamma(monitors[0], 1.0f);
        // assert(glfwGetGammaRamp(monitors[0]) != NULL);
        // glfwSetGammaRamp(monitors[0], ramp);
    }

    {
        int x, y, w, h;
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

        window = glfwCreateWindow(640, 480, "glfw3.c", NULL, NULL);
        assert(window != NULL);

        glfwSetWindowPosCallback(window, wposicb);
        glfwSetWindowSizeCallback(window, wsizecb);
        glfwSetWindowCloseCallback(window, wcloscb);
        glfwSetWindowRefreshCallback(window, wrfrscb);
        glfwSetWindowFocusCallback(window, wfocucb);
        glfwSetWindowIconifyCallback(window, wiconcb);
        glfwSetFramebufferSizeCallback(window, wfsizcb);

        assert(glfwWindowShouldClose(window) == 0);
        glfwSetWindowShouldClose(window, 1);
        assert(glfwWindowShouldClose(window) == 1);

        glfwSetWindowTitle(window, "test");
        glfwSetWindowTitle(window, "glfw3.c");

        // XXX: not implemented
        // glfwSetWindowPos(window, 1, 1);

        glfwGetWindowPos(window, &x, &y); // stub
        glfwGetWindowSize(window, &w, &h);
        assert(w == 640 && h == 480);

        glfwSetWindowSize(window, 1, 1);
        glfwGetWindowSize(window, &w, &h);
        assert(w == 1 && h == 1);

        glfwSetWindowSize(window, 640, 480);
        glfwGetFramebufferSize(window, &w, &h);

        // XXX: not implemented
        // glfwIconifyWindow(window);
        // glfwRestoreWindow(window);
        // glfwShowWindow(window);
        // glfwHideWindow(window);

        assert(glfwGetWindowMonitor(window) == NULL);
        glfwDestroyWindow(window);

        window = glfwCreateWindow(640, 480, "glfw3.c", glfwGetPrimaryMonitor(), NULL);
        assert(window != NULL);
        assert(glfwGetWindowMonitor(window) == glfwGetPrimaryMonitor());
        glfwDestroyWindow(window);

        window = glfwCreateWindow(640, 480, "glfw3.c", NULL, NULL);
        assert(window != NULL);

        assert(glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_ES_API);

        assert(glfwGetWindowUserPointer(window) == NULL);
        glfwSetWindowUserPointer(window, userptr);
        assert(glfwGetWindowUserPointer(window) == userptr);
    }

    {
        double x, y;

        glfwSetKeyCallback(window, wkeypcb);
        glfwSetCharCallback(window, wcharcb);
        glfwSetMouseButtonCallback(window, wmbutcb);
        glfwSetCursorPosCallback(window, wcurpcb);
        glfwSetCursorEnterCallback(window, wcurecb);
        glfwSetScrollCallback(window, wscrocb);

        // XXX: stub, events come immediatly
        // glfwPollEvents();
        // glfwWaitEvents();

        assert(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL);

        // XXX: not implemented
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        glfwGetKey(window, GLFW_KEY_A);
        glfwGetMouseButton(window, 0);
        glfwGetCursorPos(window, &x, &y);

        // XXX: not implemented
        // glfwSetCursorPos(window, 0, 0);
    }

    {
        // XXX: not implemented
        // glfwJoystickPresent(joy);
        // glfwGetJoystickAxes(joy, &count);
        // glfwGetJoystickButtons(joy, &count);
        // glfwGetJoystickName(joy);
    }

    {
        // XXX: not implemented
        // glfwSetClipboardString(window, "string");
        // glfwGetClipboardString(window);
    }

    {
        glfwGetTime();
        glfwSetTime(0);
    }

    {
        glfwMakeContextCurrent(window); // stub
        assert(glfwGetCurrentContext() == window);
        glfwSwapBuffers(window); // stub
        glfwSwapInterval(0); // stub
    }

    {
        assert(glfwExtensionSupported("nonexistant") == 0);
        assert(glfwGetProcAddress("nonexistant") == NULL);
    }

    glfwTerminate();

#ifdef REPORT_RESULT
    REPORT_RESULT(1);
#endif
    return 0;
}