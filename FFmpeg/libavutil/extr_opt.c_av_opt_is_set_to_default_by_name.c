#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * av_opt_find2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**) ; 
 int av_opt_is_set_to_default (void*,int /*<<< orphan*/  const*) ; 

int av_opt_is_set_to_default_by_name(void *obj, const char *name, int search_flags)
{
    const AVOption *o;
    void *target;
    if (!obj)
        return AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    if (!o)
        return AVERROR_OPTION_NOT_FOUND;
    return av_opt_is_set_to_default(target, o);
}