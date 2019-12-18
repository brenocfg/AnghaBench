#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ZSTDMT_parameter ;
struct TYPE_4__ {int overlapLog; int rsyncable; scalar_t__ jobSize; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
#define  ZSTDMT_p_jobSize 130 
#define  ZSTDMT_p_overlapLog 129 
#define  ZSTDMT_p_rsyncable 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTDMT_getMTCtxParameter(ZSTDMT_CCtx* mtctx, ZSTDMT_parameter parameter, int* value)
{
    switch (parameter) {
    case ZSTDMT_p_jobSize:
        assert(mtctx->params.jobSize <= INT_MAX);
        *value = (int)(mtctx->params.jobSize);
        break;
    case ZSTDMT_p_overlapLog:
        *value = mtctx->params.overlapLog;
        break;
    case ZSTDMT_p_rsyncable:
        *value = mtctx->params.rsyncable;
        break;
    default:
        return ERROR(parameter_unsupported);
    }
    return 0;
}