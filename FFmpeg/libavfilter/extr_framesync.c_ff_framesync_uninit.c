#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  frame_next; int /*<<< orphan*/  frame; } ;
struct TYPE_4__ {unsigned int nb_in; TYPE_3__* in; } ;
typedef  TYPE_1__ FFFrameSync ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 

void ff_framesync_uninit(FFFrameSync *fs)
{
    unsigned i;

    for (i = 0; i < fs->nb_in; i++) {
        av_frame_free(&fs->in[i].frame);
        av_frame_free(&fs->in[i].frame_next);
    }

    av_freep(&fs->in);
}