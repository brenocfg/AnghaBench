#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  formats ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {TYPE_1__ x11; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_10__ {scalar_t__ property; int /*<<< orphan*/  requestor; int /*<<< orphan*/  target; } ;
struct TYPE_13__ {TYPE_2__ xselection; } ;
typedef  TYPE_5__ XEvent ;
struct TYPE_11__ {char const* clipboardString; int /*<<< orphan*/  display; int /*<<< orphan*/  GLFW_SELECTION; int /*<<< orphan*/  CLIPBOARD; int /*<<< orphan*/  const COMPOUND_STRING; int /*<<< orphan*/  const UTF8_STRING; } ;
struct TYPE_14__ {TYPE_3__ x11; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  SelectionNotify ; 
 int /*<<< orphan*/  const XA_STRING ; 
 int /*<<< orphan*/  XCheckTypedEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  XConvertSelection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDeleteProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XFree (char*) ; 
 int /*<<< orphan*/  XGetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ _glfw ; 
 scalar_t__ _glfwGetWindowProperty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ findWindowByHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  selectDisplayConnection (int /*<<< orphan*/ *) ; 
 char const* strdup (char*) ; 

const char* _glfwPlatformGetClipboardString(_GLFWwindow* window)
{
    size_t i;
    const Atom formats[] = { _glfw.x11.UTF8_STRING,
                             _glfw.x11.COMPOUND_STRING,
                             XA_STRING };
    const size_t formatCount = sizeof(formats) / sizeof(formats[0]);

    if (findWindowByHandle(XGetSelectionOwner(_glfw.x11.display,
                                              _glfw.x11.CLIPBOARD)))
    {
        // Instead of doing a large number of X round-trips just to put this
        // string into a window property and then read it back, just return it
        return _glfw.x11.clipboardString;
    }

    free(_glfw.x11.clipboardString);
    _glfw.x11.clipboardString = NULL;

    for (i = 0;  i < formatCount;  i++)
    {
        char* data;
        XEvent event;

        XConvertSelection(_glfw.x11.display,
                          _glfw.x11.CLIPBOARD,
                          formats[i],
                          _glfw.x11.GLFW_SELECTION,
                          window->x11.handle, CurrentTime);

        // XCheckTypedEvent is used instead of XIfEvent in order not to lock
        // other threads out from the display during the entire wait period
        while (!XCheckTypedEvent(_glfw.x11.display, SelectionNotify, &event))
            selectDisplayConnection(NULL);

        if (event.xselection.property == None)
            continue;

        if (_glfwGetWindowProperty(event.xselection.requestor,
                                   event.xselection.property,
                                   event.xselection.target,
                                   (unsigned char**) &data))
        {
            _glfw.x11.clipboardString = strdup(data);
        }

        XFree(data);

        XDeleteProperty(_glfw.x11.display,
                        event.xselection.requestor,
                        event.xselection.property);

        if (_glfw.x11.clipboardString)
            break;
    }

    if (_glfw.x11.clipboardString == NULL)
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "X11: Failed to convert clipboard to string");
    }

    return _glfw.x11.clipboardString;
}