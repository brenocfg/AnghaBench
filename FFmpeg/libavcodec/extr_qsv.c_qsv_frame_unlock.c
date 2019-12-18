#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_1__* mfxMemId ;
typedef  int /*<<< orphan*/  mfxHDL ;
typedef  int /*<<< orphan*/  mfxFrameData ;
struct TYPE_4__ {int /*<<< orphan*/  hw_frame; int /*<<< orphan*/  locked_frame; } ;
typedef  TYPE_1__ QSVMid ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mfxStatus qsv_frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    QSVMid *qsv_mid = mid;

    av_frame_free(&qsv_mid->locked_frame);
    av_frame_free(&qsv_mid->hw_frame);

    return MFX_ERR_NONE;
}