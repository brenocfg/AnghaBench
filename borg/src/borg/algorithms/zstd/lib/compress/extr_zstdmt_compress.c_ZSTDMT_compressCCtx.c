#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int contentSizeFlag; } ;
struct TYPE_6__ {int /*<<< orphan*/  strategy; } ;
struct TYPE_8__ {TYPE_2__ fParams; TYPE_1__ cParams; } ;
typedef  TYPE_3__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTDMT_CCtx ;

/* Variables and functions */
 size_t ZSTDMT_compress_advanced (int /*<<< orphan*/ *,void*,size_t,void const*,size_t,int /*<<< orphan*/ *,TYPE_3__,int const) ; 
 int ZSTDMT_overlapLog_default (int /*<<< orphan*/ ) ; 
 TYPE_3__ ZSTD_getParams (int,size_t,int /*<<< orphan*/ ) ; 

size_t ZSTDMT_compressCCtx(ZSTDMT_CCtx* mtctx,
                           void* dst, size_t dstCapacity,
                     const void* src, size_t srcSize,
                           int compressionLevel)
{
    ZSTD_parameters params = ZSTD_getParams(compressionLevel, srcSize, 0);
    int const overlapLog = ZSTDMT_overlapLog_default(params.cParams.strategy);
    params.fParams.contentSizeFlag = 1;
    return ZSTDMT_compress_advanced(mtctx, dst, dstCapacity, src, srcSize, NULL, params, overlapLog);
}