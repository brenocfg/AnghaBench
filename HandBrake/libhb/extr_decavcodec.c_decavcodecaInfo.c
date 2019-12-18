#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* context; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_13__ {TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_work_object_t ;
struct TYPE_10__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_14__ {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; TYPE_1__ rate; int /*<<< orphan*/  bitrate; } ;
typedef  TYPE_5__ hb_work_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_15__ {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; TYPE_2__ time_base; int /*<<< orphan*/  bit_rate; } ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decavcodecaInfo( hb_work_object_t *w, hb_work_info_t *info )
{
    hb_work_private_t *pv = w->private_data;

    memset( info, 0, sizeof(*info) );

    if ( pv && pv->context )
    {
        AVCodecContext *context = pv->context;
        info->bitrate = context->bit_rate;
        info->rate.num = context->time_base.num;
        info->rate.den = context->time_base.den;
        info->profile = context->profile;
        info->level = context->level;
        return 1;
    }
    return 0;
}