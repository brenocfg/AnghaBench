#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_strategy ;
typedef  int /*<<< orphan*/  ZSTD_format_e ;
typedef  int ZSTD_dictAttachPref_e ;
typedef  int ZSTD_cParameter ;
struct TYPE_10__ {int enableLdm; int hashLog; int minMatchLength; int bucketSizeLog; int hashRateLog; } ;
struct TYPE_9__ {int contentSizeFlag; int checksumFlag; int noDictIDFlag; } ;
struct TYPE_8__ {int windowLog; int hashLog; int chainLog; int searchLog; int minMatch; int targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_11__ {int compressionLevel; int forceWindow; int attachDictPref; TYPE_3__ ldmParams; TYPE_2__ fParams; TYPE_1__ cParams; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNDCHECK (int const,int const) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDMT_CCtxParam_setMTCtxParameter (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 size_t ZSTDMT_CCtxParam_setNbWorkers (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ZSTDMT_p_jobSize ; 
 int /*<<< orphan*/  ZSTDMT_p_overlapLog ; 
 int /*<<< orphan*/  ZSTDMT_p_rsyncable ; 
 int ZSTD_HASHLOG_MIN ; 
 int ZSTD_WINDOWLOG_MAX ; 
#define  ZSTD_c_chainLog 150 
#define  ZSTD_c_checksumFlag 149 
#define  ZSTD_c_compressionLevel 148 
#define  ZSTD_c_contentSizeFlag 147 
#define  ZSTD_c_dictIDFlag 146 
#define  ZSTD_c_enableLongDistanceMatching 145 
#define  ZSTD_c_forceAttachDict 144 
#define  ZSTD_c_forceMaxWindow 143 
#define  ZSTD_c_format 142 
#define  ZSTD_c_hashLog 141 
#define  ZSTD_c_jobSize 140 
#define  ZSTD_c_ldmBucketSizeLog 139 
#define  ZSTD_c_ldmHashLog 138 
#define  ZSTD_c_ldmHashRateLog 137 
#define  ZSTD_c_ldmMinMatch 136 
#define  ZSTD_c_minMatch 135 
#define  ZSTD_c_nbWorkers 134 
#define  ZSTD_c_overlapLog 133 
#define  ZSTD_c_rsyncable 132 
#define  ZSTD_c_searchLog 131 
#define  ZSTD_c_strategy 130 
#define  ZSTD_c_targetLength 129 
#define  ZSTD_c_windowLog 128 
 int ZSTD_maxCLevel () ; 
 int ZSTD_minCLevel () ; 
 int /*<<< orphan*/  parameter_outOfBound ; 
 int /*<<< orphan*/  parameter_unsupported ; 

size_t ZSTD_CCtxParam_setParameter(ZSTD_CCtx_params* CCtxParams,
                                   ZSTD_cParameter param, int value)
{
    DEBUGLOG(4, "ZSTD_CCtxParam_setParameter (%i, %i)", (int)param, value);
    switch(param)
    {
    case ZSTD_c_format :
        BOUNDCHECK(ZSTD_c_format, value);
        CCtxParams->format = (ZSTD_format_e)value;
        return (size_t)CCtxParams->format;

    case ZSTD_c_compressionLevel : {
        int cLevel = value;
        if (cLevel > ZSTD_maxCLevel()) cLevel = ZSTD_maxCLevel();
        if (cLevel < ZSTD_minCLevel()) cLevel = ZSTD_minCLevel();
        if (cLevel) {  /* 0 : does not change current level */
            CCtxParams->compressionLevel = cLevel;
        }
        if (CCtxParams->compressionLevel >= 0) return CCtxParams->compressionLevel;
        return 0;  /* return type (size_t) cannot represent negative values */
    }

    case ZSTD_c_windowLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_windowLog, value);
        CCtxParams->cParams.windowLog = value;
        return CCtxParams->cParams.windowLog;

    case ZSTD_c_hashLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_hashLog, value);
        CCtxParams->cParams.hashLog = value;
        return CCtxParams->cParams.hashLog;

    case ZSTD_c_chainLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_chainLog, value);
        CCtxParams->cParams.chainLog = value;
        return CCtxParams->cParams.chainLog;

    case ZSTD_c_searchLog :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_searchLog, value);
        CCtxParams->cParams.searchLog = value;
        return value;

    case ZSTD_c_minMatch :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_minMatch, value);
        CCtxParams->cParams.minMatch = value;
        return CCtxParams->cParams.minMatch;

    case ZSTD_c_targetLength :
        BOUNDCHECK(ZSTD_c_targetLength, value);
        CCtxParams->cParams.targetLength = value;
        return CCtxParams->cParams.targetLength;

    case ZSTD_c_strategy :
        if (value!=0)   /* 0 => use default */
            BOUNDCHECK(ZSTD_c_strategy, value);
        CCtxParams->cParams.strategy = (ZSTD_strategy)value;
        return (size_t)CCtxParams->cParams.strategy;

    case ZSTD_c_contentSizeFlag :
        /* Content size written in frame header _when known_ (default:1) */
        DEBUGLOG(4, "set content size flag = %u", (value!=0));
        CCtxParams->fParams.contentSizeFlag = value != 0;
        return CCtxParams->fParams.contentSizeFlag;

    case ZSTD_c_checksumFlag :
        /* A 32-bits content checksum will be calculated and written at end of frame (default:0) */
        CCtxParams->fParams.checksumFlag = value != 0;
        return CCtxParams->fParams.checksumFlag;

    case ZSTD_c_dictIDFlag : /* When applicable, dictionary's dictID is provided in frame header (default:1) */
        DEBUGLOG(4, "set dictIDFlag = %u", (value!=0));
        CCtxParams->fParams.noDictIDFlag = !value;
        return !CCtxParams->fParams.noDictIDFlag;

    case ZSTD_c_forceMaxWindow :
        CCtxParams->forceWindow = (value != 0);
        return CCtxParams->forceWindow;

    case ZSTD_c_forceAttachDict : {
        const ZSTD_dictAttachPref_e pref = (ZSTD_dictAttachPref_e)value;
        BOUNDCHECK(ZSTD_c_forceAttachDict, pref);
        CCtxParams->attachDictPref = pref;
        return CCtxParams->attachDictPref;
    }

    case ZSTD_c_nbWorkers :
#ifndef ZSTD_MULTITHREAD
        if (value!=0) return ERROR(parameter_unsupported);
        return 0;
#else
        return ZSTDMT_CCtxParam_setNbWorkers(CCtxParams, value);
#endif

    case ZSTD_c_jobSize :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        return ZSTDMT_CCtxParam_setMTCtxParameter(CCtxParams, ZSTDMT_p_jobSize, value);
#endif

    case ZSTD_c_overlapLog :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        return ZSTDMT_CCtxParam_setMTCtxParameter(CCtxParams, ZSTDMT_p_overlapLog, value);
#endif

    case ZSTD_c_rsyncable :
#ifndef ZSTD_MULTITHREAD
        return ERROR(parameter_unsupported);
#else
        return ZSTDMT_CCtxParam_setMTCtxParameter(CCtxParams, ZSTDMT_p_rsyncable, value);
#endif

    case ZSTD_c_enableLongDistanceMatching :
        CCtxParams->ldmParams.enableLdm = (value!=0);
        return CCtxParams->ldmParams.enableLdm;

    case ZSTD_c_ldmHashLog :
        if (value!=0)   /* 0 ==> auto */
            BOUNDCHECK(ZSTD_c_ldmHashLog, value);
        CCtxParams->ldmParams.hashLog = value;
        return CCtxParams->ldmParams.hashLog;

    case ZSTD_c_ldmMinMatch :
        if (value!=0)   /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_ldmMinMatch, value);
        CCtxParams->ldmParams.minMatchLength = value;
        return CCtxParams->ldmParams.minMatchLength;

    case ZSTD_c_ldmBucketSizeLog :
        if (value!=0)   /* 0 ==> default */
            BOUNDCHECK(ZSTD_c_ldmBucketSizeLog, value);
        CCtxParams->ldmParams.bucketSizeLog = value;
        return CCtxParams->ldmParams.bucketSizeLog;

    case ZSTD_c_ldmHashRateLog :
        if (value > ZSTD_WINDOWLOG_MAX - ZSTD_HASHLOG_MIN)
            return ERROR(parameter_outOfBound);
        CCtxParams->ldmParams.hashRateLog = value;
        return CCtxParams->ldmParams.hashRateLog;

    default: return ERROR(parameter_unsupported);
    }
}