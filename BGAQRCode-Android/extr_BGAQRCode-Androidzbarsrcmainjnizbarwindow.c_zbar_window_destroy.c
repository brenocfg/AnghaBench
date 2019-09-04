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
struct TYPE_5__ {int /*<<< orphan*/  imglock; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ zbar_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_window_attach (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zbar_window_destroy (zbar_window_t *w)
{
    /* detach */
    zbar_window_attach(w, NULL, 0);
    err_cleanup(&w->err);
    _zbar_mutex_destroy(&w->imglock);
    free(w);
}