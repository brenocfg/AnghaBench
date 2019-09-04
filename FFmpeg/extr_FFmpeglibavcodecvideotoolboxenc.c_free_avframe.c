#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void free_avframe(
    void       *release_ctx,
    const void *data,
    size_t      size,
    size_t      plane_count,
    const void *plane_addresses[])
{
    AVFrame *frame = release_ctx;
    av_frame_free(&frame);
}