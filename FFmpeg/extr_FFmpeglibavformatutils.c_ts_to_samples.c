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
struct TYPE_6__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_7__ {TYPE_2__ time_base; TYPE_1__* codecpar; } ;
struct TYPE_5__ {int sample_rate; } ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  av_rescale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t ts_to_samples(AVStream *st, int64_t ts)
{
    return av_rescale(ts, st->time_base.num * st->codecpar->sample_rate, st->time_base.den);
}