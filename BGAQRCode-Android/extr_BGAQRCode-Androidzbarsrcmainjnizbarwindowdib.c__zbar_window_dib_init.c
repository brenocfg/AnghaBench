#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cleanup; int /*<<< orphan*/  draw_image; int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ zbar_window_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_window_add_format (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  dib_cleanup ; 
 int /*<<< orphan*/  dib_draw ; 
 scalar_t__* dib_formats ; 
 int /*<<< orphan*/  dib_init ; 

int _zbar_window_dib_init (zbar_window_t *w)
{
    uint32_t *fmt;
    for(fmt = dib_formats; *fmt; fmt++)
        _zbar_window_add_format(w, *fmt);

    w->init = dib_init;
    w->draw_image = dib_draw;
    w->cleanup = dib_cleanup;
    return(0);
}