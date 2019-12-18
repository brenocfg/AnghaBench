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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ VS_ERROR ; 
 int /*<<< orphan*/  VS_ERROR_TYPE ; 
 int /*<<< orphan*/  VS_INFO_TYPE ; 
 int /*<<< orphan*/  VS_MSG_TYPE ; 
 int VS_OK ; 
 int /*<<< orphan*/  VS_WARN_TYPE ; 
 int /*<<< orphan*/  av_free ; 
 int /*<<< orphan*/  av_malloc ; 
 int /*<<< orphan*/  av_mallocz ; 
 int /*<<< orphan*/  av_realloc ; 
 int /*<<< orphan*/  vs2av_log ; 
 int /*<<< orphan*/  vs_free ; 
 int /*<<< orphan*/  vs_log ; 
 int /*<<< orphan*/  vs_malloc ; 
 int /*<<< orphan*/  vs_realloc ; 
 int /*<<< orphan*/  vs_zalloc ; 

void ff_vs_init(void)
{
    vs_malloc  = av_malloc;
    vs_zalloc  = av_mallocz;
    vs_realloc = av_realloc;
    vs_free    = av_free;

    VS_ERROR_TYPE = AV_LOG_ERROR;
    VS_WARN_TYPE  = AV_LOG_WARNING;
    VS_INFO_TYPE  = AV_LOG_INFO;
    VS_MSG_TYPE   = AV_LOG_VERBOSE;

    vs_log   = vs2av_log;

    VS_ERROR = 0;
    VS_OK    = 1;
}