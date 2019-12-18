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
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  int /*<<< orphan*/  mfxMemId ;
typedef  int /*<<< orphan*/  mfxHDL ;
typedef  int /*<<< orphan*/  mfxFrameData ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_ERR_UNSUPPORTED ; 

__attribute__((used)) static mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    return MFX_ERR_UNSUPPORTED;
}