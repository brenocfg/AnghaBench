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
typedef  int /*<<< orphan*/  workSpace ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  HUF_DTable ;

/* Variables and functions */
 int HUF_DECOMPRESS_WORKSPACE_SIZE_U32 ; 
 size_t HUF_decompress1X_DCtx_wksp (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int /*<<< orphan*/ *,int) ; 

size_t HUF_decompress1X_DCtx(HUF_DTable* dctx, void* dst, size_t dstSize,
                             const void* cSrc, size_t cSrcSize)
{
    U32 workSpace[HUF_DECOMPRESS_WORKSPACE_SIZE_U32];
    return HUF_decompress1X_DCtx_wksp(dctx, dst, dstSize, cSrc, cSrcSize,
                                      workSpace, sizeof(workSpace));
}