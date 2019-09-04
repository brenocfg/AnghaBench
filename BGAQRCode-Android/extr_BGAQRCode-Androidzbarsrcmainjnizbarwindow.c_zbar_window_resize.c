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
struct TYPE_7__ {scalar_t__ x; } ;
struct TYPE_8__ {unsigned int width; unsigned int height; TYPE_1__ scaled_size; } ;
typedef  TYPE_2__ zbar_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_window_resize (TYPE_2__*) ; 
 scalar_t__ window_lock (TYPE_2__*) ; 
 int window_unlock (TYPE_2__*) ; 

int zbar_window_resize (zbar_window_t *w,
                        unsigned width,
                        unsigned height)
{
    if(window_lock(w))
        return(-1);
    w->width = width;
    w->height = height;
    w->scaled_size.x = 0;
    _zbar_window_resize(w);
    return(window_unlock(w));
}