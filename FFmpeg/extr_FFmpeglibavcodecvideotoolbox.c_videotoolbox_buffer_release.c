#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  pixbuf; int /*<<< orphan*/  hw_frames_ctx; } ;
typedef  TYPE_1__ VTHWFrame ;

/* Variables and functions */
 int /*<<< orphan*/  CVPixelBufferRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void videotoolbox_buffer_release(void *opaque, uint8_t *data)
{
    VTHWFrame *ref = (VTHWFrame *)data;
    av_buffer_unref(&ref->hw_frames_ctx);
    CVPixelBufferRelease(ref->pixbuf);

    av_free(data);
}