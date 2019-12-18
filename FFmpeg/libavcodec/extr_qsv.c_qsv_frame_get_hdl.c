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
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  scalar_t__ mfxMemId ;
typedef  int /*<<< orphan*/  mfxHDL ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ QSVMid ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_ERR_NONE ; 

__attribute__((used)) static mfxStatus qsv_frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    QSVMid *qsv_mid = (QSVMid*)mid;
    *hdl = qsv_mid->handle;
    return MFX_ERR_NONE;
}