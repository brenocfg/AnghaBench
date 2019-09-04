#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * hdd; } ;
typedef  TYPE_1__ zbar_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  DrawDibClose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfw_cleanup (zbar_window_t *w)
{
    if(w->hdd) {
        DrawDibClose(w->hdd);
        w->hdd = NULL;
    }
    return(0);
}