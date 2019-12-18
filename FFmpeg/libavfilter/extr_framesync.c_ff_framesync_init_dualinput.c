#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__** inputs; } ;
struct TYPE_11__ {TYPE_2__* in; } ;
struct TYPE_10__ {int sync; void* after; int /*<<< orphan*/  before; int /*<<< orphan*/  time_base; } ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ FFFrameSync ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 void* EXT_INFINITY ; 
 int /*<<< orphan*/  EXT_NULL ; 
 int /*<<< orphan*/  EXT_STOP ; 
 int ff_framesync_init (TYPE_3__*,TYPE_4__*,int) ; 

int ff_framesync_init_dualinput(FFFrameSync *fs, AVFilterContext *parent)
{
    int ret;

    ret = ff_framesync_init(fs, parent, 2);
    if (ret < 0)
        return ret;
    fs->in[0].time_base = parent->inputs[0]->time_base;
    fs->in[1].time_base = parent->inputs[1]->time_base;
    fs->in[0].sync   = 2;
    fs->in[0].before = EXT_STOP;
    fs->in[0].after  = EXT_INFINITY;
    fs->in[1].sync   = 1;
    fs->in[1].before = EXT_NULL;
    fs->in[1].after  = EXT_INFINITY;
    return 0;
}