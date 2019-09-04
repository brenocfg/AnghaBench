#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * formats; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_6__ {int /*<<< orphan*/ * xv_ports; } ;
typedef  TYPE_2__ window_state_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  XvPortID ;

/* Variables and functions */
 int _zbar_window_add_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int xv_add_format (zbar_window_t *w,
                                 uint32_t fmt,
                                 XvPortID port)
{
    int i = _zbar_window_add_format(w, fmt);

    window_state_t *x = w->state;
    if(!w->formats[i + 1])
        x->xv_ports = realloc(x->xv_ports, (i + 1) * sizeof(*x->xv_ports));

    /* FIXME could prioritize by something (rate? size?) */
    x->xv_ports[i] = port;
    return(i);
}