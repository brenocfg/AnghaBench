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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int flags; int offset; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int AV_OPT_FLAG_READONLY ; 
 int /*<<< orphan*/  EINVAL ; 
 TYPE_1__* av_opt_find2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**) ; 
 int write_number (void*,TYPE_1__ const*,void*,double,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_number(void *obj, const char *name, double num, int den, int64_t intnum,
                      int search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    if (!o || !target_obj)
        return AVERROR_OPTION_NOT_FOUND;

    if (o->flags & AV_OPT_FLAG_READONLY)
        return AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;
    return write_number(obj, o, dst, num, den, intnum);
}