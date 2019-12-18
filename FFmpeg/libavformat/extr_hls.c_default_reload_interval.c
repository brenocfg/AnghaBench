#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct playlist {int n_segments; int /*<<< orphan*/  target_duration; TYPE_1__** segments; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  duration; } ;

/* Variables and functions */

__attribute__((used)) static int64_t default_reload_interval(struct playlist *pls)
{
    return pls->n_segments > 0 ?
                          pls->segments[pls->n_segments - 1]->duration :
                          pls->target_duration;
}