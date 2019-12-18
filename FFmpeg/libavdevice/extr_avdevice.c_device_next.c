#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ category; } ;
struct TYPE_5__ {TYPE_3__* priv_class; } ;
struct TYPE_4__ {TYPE_3__* priv_class; } ;
typedef  TYPE_1__ AVOutputFormat ;
typedef  TYPE_2__ AVInputFormat ;
typedef  scalar_t__ AVClassCategory ;
typedef  TYPE_3__ AVClass ;

/* Variables and functions */
 scalar_t__ AV_CLASS_CATEGORY_NA ; 
 void* av_iformat_next (void*) ; 
 void* av_oformat_next (void*) ; 

__attribute__((used)) static void *device_next(void *prev, int output,
                         AVClassCategory c1, AVClassCategory c2)
{
    const AVClass *pc;
    AVClassCategory category = AV_CLASS_CATEGORY_NA;
    do {
        if (output) {
            if (!(prev = av_oformat_next(prev)))
                break;
            pc = ((AVOutputFormat *)prev)->priv_class;
        } else {
            if (!(prev = av_iformat_next(prev)))
                break;
            pc = ((AVInputFormat *)prev)->priv_class;
        }
        if (!pc)
            continue;
        category = pc->category;
    } while (category != c1 && category != c2);
    return prev;
}