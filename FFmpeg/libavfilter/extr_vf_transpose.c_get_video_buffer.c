#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ passthrough; } ;
typedef  TYPE_2__ TransContext ;
struct TYPE_9__ {TYPE_1__* dst; } ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/ * ff_default_get_video_buffer (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/ * ff_null_get_video_buffer (TYPE_3__*,int,int) ; 

__attribute__((used)) static AVFrame *get_video_buffer(AVFilterLink *inlink, int w, int h)
{
    TransContext *s = inlink->dst->priv;

    return s->passthrough ?
        ff_null_get_video_buffer   (inlink, w, h) :
        ff_default_get_video_buffer(inlink, w, h);
}