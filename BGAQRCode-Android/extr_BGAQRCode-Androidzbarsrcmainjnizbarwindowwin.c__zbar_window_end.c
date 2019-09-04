#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  display; TYPE_1__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_4__ {int /*<<< orphan*/ * hdc; } ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RestoreDC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ValidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int _zbar_window_end (zbar_window_t *w)
{
    HDC hdc = w->state->hdc;
    w->state->hdc = NULL;
    RestoreDC(hdc, -1);
    ReleaseDC(w->display, hdc);
    ValidateRect(w->display, NULL);
    return(0);
}