#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char XcursorPixel ;
struct TYPE_10__ {int xhot; int yhot; unsigned char* pixels; } ;
typedef  TYPE_2__ XcursorImage ;
struct TYPE_9__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {TYPE_1__ x11; } ;
struct TYPE_11__ {int width; int height; scalar_t__ pixels; } ;
typedef  TYPE_3__ GLFWimage ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  None ; 
 TYPE_2__* XcursorImageCreate (int,int) ; 
 int /*<<< orphan*/  XcursorImageDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  XcursorImageLoadCursor (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__ _glfw ; 

Cursor _glfwCreateCursor(const GLFWimage* image, int xhot, int yhot)
{
    int i;
    Cursor cursor;

    XcursorImage* native = XcursorImageCreate(image->width, image->height);
    if (native == NULL)
        return None;

    native->xhot = xhot;
    native->yhot = yhot;

    unsigned char* source = (unsigned char*) image->pixels;
    XcursorPixel* target = native->pixels;

    for (i = 0;  i < image->width * image->height;  i++, target++, source += 4)
    {
        *target = (source[3] << 24) |
                  (source[0] << 16) |
                  (source[1] <<  8) |
                   source[2];
    }

    cursor = XcursorImageLoadCursor(_glfw.x11.display, native);
    XcursorImageDestroy(native);

    return cursor;
}