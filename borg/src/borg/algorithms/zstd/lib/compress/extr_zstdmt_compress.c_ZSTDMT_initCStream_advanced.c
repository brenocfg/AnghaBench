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
struct TYPE_9__ {int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;
struct TYPE_10__ {TYPE_2__ params; } ;
typedef  TYPE_3__ ZSTDMT_CCtx ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_initCStream_internal (TYPE_3__*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,unsigned long long) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 

size_t ZSTDMT_initCStream_advanced(ZSTDMT_CCtx* mtctx,
                             const void* dict, size_t dictSize,
                                   ZSTD_parameters params,
                                   unsigned long long pledgedSrcSize)
{
    ZSTD_CCtx_params cctxParams = mtctx->params;  /* retrieve sticky params */
    DEBUGLOG(4, "ZSTDMT_initCStream_advanced (pledgedSrcSize=%u)", (U32)pledgedSrcSize);
    cctxParams.cParams = params.cParams;
    cctxParams.fParams = params.fParams;
    return ZSTDMT_initCStream_internal(mtctx, dict, dictSize, ZSTD_dct_auto, NULL,
                                       cctxParams, pledgedSrcSize);
}