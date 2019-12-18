#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobParams ;
struct TYPE_5__ {int /*<<< orphan*/  compressionLevel; int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZSTD_CCtx_params ZSTDMT_initJobCCtxParams(ZSTD_CCtx_params const params)
{
    ZSTD_CCtx_params jobParams;
    memset(&jobParams, 0, sizeof(jobParams));

    jobParams.cParams = params.cParams;
    jobParams.fParams = params.fParams;
    jobParams.compressionLevel = params.compressionLevel;

    return jobParams;
}