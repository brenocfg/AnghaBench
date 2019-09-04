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
struct TYPE_5__ {void* protocol_blacklist; void* protocol_whitelist; void* format_whitelist; void* codec_whitelist; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* av_strdup (void*) ; 

int ff_copy_whiteblacklists(AVFormatContext *dst, const AVFormatContext *src)
{
    av_assert0(!dst->codec_whitelist &&
               !dst->format_whitelist &&
               !dst->protocol_whitelist &&
               !dst->protocol_blacklist);
    dst-> codec_whitelist = av_strdup(src->codec_whitelist);
    dst->format_whitelist = av_strdup(src->format_whitelist);
    dst->protocol_whitelist = av_strdup(src->protocol_whitelist);
    dst->protocol_blacklist = av_strdup(src->protocol_blacklist);
    if (   (src-> codec_whitelist && !dst-> codec_whitelist)
        || (src->  format_whitelist && !dst->  format_whitelist)
        || (src->protocol_whitelist && !dst->protocol_whitelist)
        || (src->protocol_blacklist && !dst->protocol_blacklist)) {
        av_log(dst, AV_LOG_ERROR, "Failed to duplicate black/whitelist\n");
        return AVERROR(ENOMEM);
    }
    return 0;
}