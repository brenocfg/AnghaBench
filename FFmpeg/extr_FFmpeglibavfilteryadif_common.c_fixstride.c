#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/  linesize; scalar_t__ data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int /*<<< orphan*/  av_frame_move_ref (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  av_image_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_default_get_video_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixstride(AVFilterLink *link, AVFrame *f)
{
    AVFrame *dst = ff_default_get_video_buffer(link, f->width, f->height);
    if(!dst)
        return;
    av_frame_copy_props(dst, f);
    av_image_copy(dst->data, dst->linesize,
                  (const uint8_t **)f->data, f->linesize,
                  dst->format, dst->width, dst->height);
    av_frame_unref(f);
    av_frame_move_ref(f, dst);
    av_frame_free(&dst);
}