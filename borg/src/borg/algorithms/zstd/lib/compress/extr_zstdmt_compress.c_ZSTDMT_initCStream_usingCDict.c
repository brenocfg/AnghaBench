#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
struct TYPE_6__ {int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;
struct TYPE_7__ {TYPE_1__ params; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_initCStream_internal (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__,unsigned long long) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_getCParamsFromCDict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dictionary_wrong ; 

size_t ZSTDMT_initCStream_usingCDict(ZSTDMT_CCtx* mtctx,
                               const ZSTD_CDict* cdict,
                                     ZSTD_frameParameters fParams,
                                     unsigned long long pledgedSrcSize)
{
    ZSTD_CCtx_params cctxParams = mtctx->params;
    if (cdict==NULL) return ERROR(dictionary_wrong);   /* method incompatible with NULL cdict */
    cctxParams.cParams = ZSTD_getCParamsFromCDict(cdict);
    cctxParams.fParams = fParams;
    return ZSTDMT_initCStream_internal(mtctx, NULL, 0 /*dictSize*/, ZSTD_dct_auto, cdict,
                                       cctxParams, pledgedSrcSize);
}