#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hostageByte; scalar_t__ legacyVersion; scalar_t__ outEnd; scalar_t__ outStart; scalar_t__ inPos; scalar_t__ lhSize; int /*<<< orphan*/  streamStage; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 size_t ZSTD_FRAMEHEADERSIZE_PREFIX ; 
 int /*<<< orphan*/  zdss_loadHeader ; 

size_t ZSTD_resetDStream(ZSTD_DStream* dctx)
{
    DEBUGLOG(4, "ZSTD_resetDStream");
    dctx->streamStage = zdss_loadHeader;
    dctx->lhSize = dctx->inPos = dctx->outStart = dctx->outEnd = 0;
    dctx->legacyVersion = 0;
    dctx->hostageByte = 0;
    return ZSTD_FRAMEHEADERSIZE_PREFIX;
}