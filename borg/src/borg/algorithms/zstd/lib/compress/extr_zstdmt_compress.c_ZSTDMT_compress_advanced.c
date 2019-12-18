#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_9__ {int overlapLog; int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;
struct TYPE_10__ {TYPE_2__ params; } ;
typedef  TYPE_3__ ZSTDMT_CCtx ;

/* Variables and functions */
 size_t ZSTDMT_compress_advanced_internal (TYPE_3__*,void*,size_t,void const*,size_t,int /*<<< orphan*/  const*,TYPE_2__) ; 
 int ZSTD_OVERLAPLOG_MAX ; 
 int ZSTD_OVERLAPLOG_MIN ; 
 int /*<<< orphan*/  assert (int) ; 

size_t ZSTDMT_compress_advanced(ZSTDMT_CCtx* mtctx,
                                void* dst, size_t dstCapacity,
                          const void* src, size_t srcSize,
                          const ZSTD_CDict* cdict,
                                ZSTD_parameters params,
                                int overlapLog)
{
    ZSTD_CCtx_params cctxParams = mtctx->params;
    cctxParams.cParams = params.cParams;
    cctxParams.fParams = params.fParams;
    assert(ZSTD_OVERLAPLOG_MIN <= overlapLog && overlapLog <= ZSTD_OVERLAPLOG_MAX);
    cctxParams.overlapLog = overlapLog;
    return ZSTDMT_compress_advanced_internal(mtctx,
                                             dst, dstCapacity,
                                             src, srcSize,
                                             cdict, cctxParams);
}