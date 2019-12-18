#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame1; int /*<<< orphan*/  frame2; } ;
typedef  TYPE_1__ RASCContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_plane (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_frames(AVCodecContext *avctx)
{
    RASCContext *s = avctx->priv_data;
    int ret;

    av_frame_unref(s->frame1);
    av_frame_unref(s->frame2);
    if ((ret = ff_get_buffer(avctx, s->frame1, 0)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, s->frame2, 0)) < 0)
        return ret;

    clear_plane(avctx, s->frame2);
    clear_plane(avctx, s->frame1);

    return 0;
}