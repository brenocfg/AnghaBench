#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  int /*<<< orphan*/  mfxHDL ;
struct TYPE_3__ {size_t NumFrameActual; int /*<<< orphan*/ * mids; } ;
typedef  TYPE_1__ mfxFrameAllocResponse ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 

__attribute__((used)) static mfxStatus qsv_frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    av_buffer_unref((AVBufferRef**)&resp->mids[resp->NumFrameActual]);
    av_buffer_unref((AVBufferRef**)&resp->mids[resp->NumFrameActual + 1]);
    av_freep(&resp->mids);
    return MFX_ERR_NONE;
}