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
struct TYPE_3__ {int jobSize; int overlapLog; int rsyncable; } ;
typedef  TYPE_1__ ZSTD_CCtx_params ;
typedef  int ZSTDMT_parameter ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int ZSTDMT_JOBSIZE_MAX ; 
 int ZSTDMT_JOBSIZE_MIN ; 
#define  ZSTDMT_p_jobSize 130 
#define  ZSTDMT_p_overlapLog 129 
#define  ZSTDMT_p_rsyncable 128 
 int ZSTD_OVERLAPLOG_MAX ; 
 int ZSTD_OVERLAPLOG_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t
ZSTDMT_CCtxParam_setMTCtxParameter(ZSTD_CCtx_params* params,
                                   ZSTDMT_parameter parameter,
                                   int value)
{
    DEBUGLOG(4, "ZSTDMT_CCtxParam_setMTCtxParameter");
    switch(parameter)
    {
    case ZSTDMT_p_jobSize :
        DEBUGLOG(4, "ZSTDMT_CCtxParam_setMTCtxParameter : set jobSize to %i", value);
        if ( value != 0  /* default */
          && value < ZSTDMT_JOBSIZE_MIN)
            value = ZSTDMT_JOBSIZE_MIN;
        assert(value >= 0);
        if (value > ZSTDMT_JOBSIZE_MAX) value = ZSTDMT_JOBSIZE_MAX;
        params->jobSize = value;
        return value;

    case ZSTDMT_p_overlapLog :
        DEBUGLOG(4, "ZSTDMT_p_overlapLog : %i", value);
        if (value < ZSTD_OVERLAPLOG_MIN) value = ZSTD_OVERLAPLOG_MIN;
        if (value > ZSTD_OVERLAPLOG_MAX) value = ZSTD_OVERLAPLOG_MAX;
        params->overlapLog = value;
        return value;

    case ZSTDMT_p_rsyncable :
        value = (value != 0);
        params->rsyncable = value;
        return value;

    default :
        return ERROR(parameter_unsupported);
    }
}