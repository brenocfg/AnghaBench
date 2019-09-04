#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* name; } ;
struct TYPE_4__ {int nb_tracked_methods; scalar_t__ tracked_methods_size; TYPE_3__* tracked_methods; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 

__attribute__((used)) static void free_tracked_methods(RTMPContext *rt)
{
    int i;

    for (i = 0; i < rt->nb_tracked_methods; i ++)
        av_freep(&rt->tracked_methods[i].name);
    av_freep(&rt->tracked_methods);
    rt->tracked_methods_size = 0;
    rt->nb_tracked_methods   = 0;
}