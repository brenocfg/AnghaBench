#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AV_LOG_DEBUG ; 
 int AV_LOG_ERROR ; 
 int AV_LOG_QUIET ; 
 int AV_LOG_TRACE ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
 int WELS_LOG_DEBUG ; 
 int WELS_LOG_DETAIL ; 
 int WELS_LOG_ERROR ; 
 int WELS_LOG_INFO ; 
 int WELS_LOG_WARNING ; 

__attribute__((used)) static int libopenh264_to_ffmpeg_log_level(int libopenh264_log_level)
{
    if      (libopenh264_log_level >= WELS_LOG_DETAIL)  return AV_LOG_TRACE;
    else if (libopenh264_log_level >= WELS_LOG_DEBUG)   return AV_LOG_DEBUG;
    else if (libopenh264_log_level >= WELS_LOG_INFO)    return AV_LOG_VERBOSE;
    else if (libopenh264_log_level >= WELS_LOG_WARNING) return AV_LOG_WARNING;
    else if (libopenh264_log_level >= WELS_LOG_ERROR)   return AV_LOG_ERROR;
    else                                                return AV_LOG_QUIET;
}