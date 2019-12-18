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
typedef  int /*<<< orphan*/  ZSTD_buffered_policy_e ;
struct TYPE_4__ {int /*<<< orphan*/  cParams; int /*<<< orphan*/  ldmParams; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;
typedef  scalar_t__ U64 ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int /*<<< orphan*/  ZSTD_equivalentCParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_equivalentLdmParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_sufficientBuff (size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static U32 ZSTD_equivalentParams(ZSTD_CCtx_params params1,
                                 ZSTD_CCtx_params params2,
                                 size_t buffSize1,
                                 size_t maxNbSeq1, size_t maxNbLit1,
                                 ZSTD_buffered_policy_e buffPol2,
                                 U64 pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_equivalentParams: pledgedSrcSize=%u", (U32)pledgedSrcSize);
    if (!ZSTD_equivalentCParams(params1.cParams, params2.cParams)) {
      DEBUGLOG(4, "ZSTD_equivalentCParams() == 0");
      return 0;
    }
    if (!ZSTD_equivalentLdmParams(params1.ldmParams, params2.ldmParams)) {
      DEBUGLOG(4, "ZSTD_equivalentLdmParams() == 0");
      return 0;
    }
    if (!ZSTD_sufficientBuff(buffSize1, maxNbSeq1, maxNbLit1, buffPol2,
                             params2.cParams, pledgedSrcSize)) {
      DEBUGLOG(4, "ZSTD_sufficientBuff() == 0");
      return 0;
    }
    return 1;
}