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
struct TYPE_3__ {int nb_tracked_methods; int /*<<< orphan*/ * tracked_methods; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void del_tracked_method(RTMPContext *rt, int index)
{
    memmove(&rt->tracked_methods[index], &rt->tracked_methods[index + 1],
            sizeof(*rt->tracked_methods) * (rt->nb_tracked_methods - index - 1));
    rt->nb_tracked_methods--;
}