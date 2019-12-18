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
struct TYPE_4__ {int /*<<< orphan*/  available; } ;
struct TYPE_5__ {int* nativeKeys; char const* keyName; int /*<<< orphan*/  display; int /*<<< orphan*/ * publicKeys; TYPE_1__ xkb; } ;
struct TYPE_6__ {TYPE_2__ x11; } ;
typedef  scalar_t__ KeySym ;

/* Variables and functions */
 int GLFW_KEY_UNKNOWN ; 
 scalar_t__ NoSymbol ; 
 scalar_t__ XkbKeycodeToKeysym (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XkbTranslateKeySym (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char const*,int,int*) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwIsPrintable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

const char* _glfwPlatformGetKeyName(int key, int scancode)
{
    KeySym keysym;
    int extra;

    if (!_glfw.x11.xkb.available)
        return NULL;

    if (key != GLFW_KEY_UNKNOWN)
        scancode = _glfw.x11.nativeKeys[key];

    if (!_glfwIsPrintable(_glfw.x11.publicKeys[scancode]))
        return NULL;

    keysym = XkbKeycodeToKeysym(_glfw.x11.display, scancode, 0, 0);
    if (keysym == NoSymbol)
      return NULL;

    XkbTranslateKeySym(_glfw.x11.display, &keysym, 0,
                       _glfw.x11.keyName, sizeof(_glfw.x11.keyName),
                       &extra);

    if (!strlen(_glfw.x11.keyName))
        return NULL;

    return _glfw.x11.keyName;
}