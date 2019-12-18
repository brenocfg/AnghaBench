#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyImage (TYPE_1__*) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colormap ; 
 int /*<<< orphan*/  display ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gc ; 
 scalar_t__ have_colormap ; 
 scalar_t__ have_gc ; 
 scalar_t__ have_nondefault_visual ; 
 scalar_t__ have_window ; 
 char* image_data ; 
 int /*<<< orphan*/  visual_list ; 
 int /*<<< orphan*/  window ; 
 TYPE_1__* ximage ; 

__attribute__((used)) static void rpng_x_cleanup(void)
{
    if (image_data) {
        free(image_data);
        image_data = NULL;
    }

    if (ximage) {
        if (ximage->data) {
            free(ximage->data);           /* we allocated it, so we free it */
            ximage->data = (char *)NULL;  /*  instead of XDestroyImage() */
        }
        XDestroyImage(ximage);
        ximage = NULL;
    }

    if (have_gc)
        XFreeGC(display, gc);

    if (have_window)
        XDestroyWindow(display, window);

    if (have_colormap)
        XFreeColormap(display, colormap);

    if (have_nondefault_visual)
        XFree(visual_list);
}