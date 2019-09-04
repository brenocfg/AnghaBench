#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int overlay; } ;
typedef  TYPE_1__ zbar_window_t ;

/* Variables and functions */
 scalar_t__ window_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  window_unlock (TYPE_1__*) ; 

void zbar_window_set_overlay (zbar_window_t *w,
                              int lvl)
{
    if(lvl < 0)
        lvl = 0;
    if(lvl > 2)
        lvl = 2;
    if(window_lock(w))
        return;
    if(w->overlay != lvl)
        w->overlay = lvl;
    (void)window_unlock(w);
}