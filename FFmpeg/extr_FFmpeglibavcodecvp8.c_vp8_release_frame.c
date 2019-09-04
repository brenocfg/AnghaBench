#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tf; int /*<<< orphan*/ * hwaccel_picture_private; int /*<<< orphan*/  hwaccel_priv_buf; int /*<<< orphan*/  seg_map; } ;
typedef  TYPE_1__ VP8Frame ;
struct TYPE_6__ {int /*<<< orphan*/  avctx; } ;
typedef  TYPE_2__ VP8Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp8_release_frame(VP8Context *s, VP8Frame *f)
{
    av_buffer_unref(&f->seg_map);
    av_buffer_unref(&f->hwaccel_priv_buf);
    f->hwaccel_picture_private = NULL;
    ff_thread_release_buffer(s->avctx, &f->tf);
}