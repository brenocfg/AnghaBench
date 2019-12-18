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
typedef  scalar_t__ ZSTD_ResetDirective ;
struct TYPE_4__ {scalar_t__ streamStage; int /*<<< orphan*/  maxWindowSize; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_MAXWINDOWSIZE_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_f_zstd1 ; 
 int /*<<< orphan*/  ZSTD_initDStream (TYPE_1__*) ; 
 scalar_t__ ZSTD_reset_parameters ; 
 scalar_t__ ZSTD_reset_session_and_parameters ; 
 scalar_t__ ZSTD_reset_session_only ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zdss_init ; 

size_t ZSTD_DCtx_reset(ZSTD_DCtx* dctx, ZSTD_ResetDirective reset)
{
    if ( (reset == ZSTD_reset_session_only)
      || (reset == ZSTD_reset_session_and_parameters) ) {
        (void)ZSTD_initDStream(dctx);
    }
    if ( (reset == ZSTD_reset_parameters)
      || (reset == ZSTD_reset_session_and_parameters) ) {
        if (dctx->streamStage != zdss_init)
            return ERROR(stage_wrong);
        dctx->format = ZSTD_f_zstd1;
        dctx->maxWindowSize = ZSTD_MAXWINDOWSIZE_DEFAULT;
    }
    return 0;
}