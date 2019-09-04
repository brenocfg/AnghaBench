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
struct TYPE_5__ {int id; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int nb_tracked_methods; int tracked_methods_size; TYPE_2__* tracked_methods; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_reallocp (TYPE_2__**,int) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 

__attribute__((used)) static int add_tracked_method(RTMPContext *rt, const char *name, int id)
{
    int err;

    if (rt->nb_tracked_methods + 1 > rt->tracked_methods_size) {
        rt->tracked_methods_size = (rt->nb_tracked_methods + 1) * 2;
        if ((err = av_reallocp(&rt->tracked_methods, rt->tracked_methods_size *
                               sizeof(*rt->tracked_methods))) < 0) {
            rt->nb_tracked_methods = 0;
            rt->tracked_methods_size = 0;
            return err;
        }
    }

    rt->tracked_methods[rt->nb_tracked_methods].name = av_strdup(name);
    if (!rt->tracked_methods[rt->nb_tracked_methods].name)
        return AVERROR(ENOMEM);
    rt->tracked_methods[rt->nb_tracked_methods].id = id;
    rt->nb_tracked_methods++;

    return 0;
}