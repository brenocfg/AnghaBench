#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {TYPE_2__* internal; } ;
struct TYPE_6__ {TYPE_1__* priv_pts; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 

int64_t av_stream_get_end_pts(const AVStream *st)
{
    if (st->internal->priv_pts) {
        return st->internal->priv_pts->val;
    } else
        return AV_NOPTS_VALUE;
}