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
struct TYPE_6__ {int /*<<< orphan*/  display; TYPE_3__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_5__ {int /*<<< orphan*/ * xv; } ;
struct TYPE_7__ {int num_xv_adaptors; scalar_t__* xv_adaptors; scalar_t__* xv_ports; TYPE_1__ img; } ;
typedef  TYPE_3__ window_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XvUngrabPort (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 

__attribute__((used)) static int xv_cleanup (zbar_window_t *w)
{
    window_state_t *x = w->state;
    if(x->img.xv) {
        XFree(x->img.xv);
        x->img.xv = NULL;
    }
    int i;
    for(i = 0; i < x->num_xv_adaptors; i++)
        if(x->xv_adaptors[i]) {
            XvUngrabPort(w->display, x->xv_adaptors[i], CurrentTime);
            x->xv_adaptors[i] = 0;
        }
    free(x->xv_ports);
    free(x->xv_adaptors);
    x->xv_ports = NULL;
    x->num_xv_adaptors = 0;
    x->xv_adaptors = NULL;
    return(0);
}