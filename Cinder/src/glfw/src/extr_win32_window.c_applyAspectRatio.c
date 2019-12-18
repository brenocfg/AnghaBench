#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ denom; scalar_t__ numer; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_8__ {int bottom; int top; int right; int left; } ;
typedef  TYPE_2__ RECT ;

/* Variables and functions */
 int WMSZ_BOTTOM ; 
 int WMSZ_BOTTOMLEFT ; 
 int WMSZ_BOTTOMRIGHT ; 
 int WMSZ_LEFT ; 
 int WMSZ_RIGHT ; 
 int WMSZ_TOP ; 
 int WMSZ_TOPLEFT ; 
 int WMSZ_TOPRIGHT ; 
 int /*<<< orphan*/  getFullWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  getWindowExStyle (TYPE_1__*) ; 
 int /*<<< orphan*/  getWindowStyle (TYPE_1__*) ; 

__attribute__((used)) static void applyAspectRatio(_GLFWwindow* window, int edge, RECT* area)
{
    int xoff, yoff;
    const float ratio = (float) window->numer / (float) window->denom;

    getFullWindowSize(getWindowStyle(window), getWindowExStyle(window),
                      0, 0, &xoff, &yoff);

    if (edge == WMSZ_LEFT  || edge == WMSZ_BOTTOMLEFT ||
        edge == WMSZ_RIGHT || edge == WMSZ_BOTTOMRIGHT)
    {
        area->bottom = area->top + yoff +
            (int) ((area->right - area->left - xoff) / ratio);
    }
    else if (edge == WMSZ_TOPLEFT || edge == WMSZ_TOPRIGHT)
    {
        area->top = area->bottom - yoff -
            (int) ((area->right - area->left - xoff) / ratio);
    }
    else if (edge == WMSZ_TOP || edge == WMSZ_BOTTOM)
    {
        area->right = area->left + xoff +
            (int) ((area->bottom - area->top - yoff) * ratio);
    }
}