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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_5__ {int offset; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
 TYPE_1__* av_opt_find2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**) ; 
 int read_number (TYPE_1__ const*,void*,double*,int*,int*) ; 

__attribute__((used)) static int get_number(void *obj, const char *name, const AVOption **o_out, double *num, int *den, int64_t *intnum,
                      int search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    if (!o || !target_obj)
        goto error;

    dst = ((uint8_t *)target_obj) + o->offset;

    if (o_out) *o_out= o;

    return read_number(o, dst, num, den, intnum);

error:
    *den    =
    *intnum = 0;
    return -1;
}