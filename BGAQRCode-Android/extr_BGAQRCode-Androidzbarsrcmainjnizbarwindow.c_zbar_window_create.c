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
struct TYPE_4__ {int overlay; int /*<<< orphan*/  imglock; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ zbar_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_MOD_WINDOW ; 
 int /*<<< orphan*/  _zbar_mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  err_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

zbar_window_t *zbar_window_create ()
{
    zbar_window_t *w = calloc(1, sizeof(zbar_window_t));
    if(!w)
        return(NULL);
    err_init(&w->err, ZBAR_MOD_WINDOW);
    w->overlay = 1;
    (void)_zbar_mutex_init(&w->imglock);
    return(w);
}