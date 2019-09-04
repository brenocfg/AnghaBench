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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void mids_buf_free(void *opaque, uint8_t *data)
{
    AVBufferRef *hw_frames_ref = opaque;
    av_buffer_unref(&hw_frames_ref);
    av_freep(&data);
}