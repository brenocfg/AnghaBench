#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_5__ {int /*<<< orphan*/ * x; } ;
struct TYPE_7__ {TYPE_1__ img; } ;
typedef  TYPE_3__ window_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ximage_cleanup (zbar_window_t *w)
{
    window_state_t *x = w->state;
    if(x->img.x)
        free(x->img.x);
    x->img.x = NULL;
    return(0);
}