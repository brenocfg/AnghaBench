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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  rtmp; } ;
typedef  int /*<<< orphan*/  RTMP ;
typedef  TYPE_2__ LibRTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVERROR_UNKNOWN ; 
 int AVSEEK_FLAG_BACKWARD ; 
 int AVSEEK_FLAG_BYTE ; 
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  RTMP_SendSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_rnd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t rtmp_read_seek(URLContext *s, int stream_index,
                              int64_t timestamp, int flags)
{
    LibRTMPContext *ctx = s->priv_data;
    RTMP *r = &ctx->rtmp;

    if (flags & AVSEEK_FLAG_BYTE)
        return AVERROR(ENOSYS);

    /* seeks are in milliseconds */
    if (stream_index < 0)
        timestamp = av_rescale_rnd(timestamp, 1000, AV_TIME_BASE,
            flags & AVSEEK_FLAG_BACKWARD ? AV_ROUND_DOWN : AV_ROUND_UP);

    if (!RTMP_SendSeek(r, timestamp))
        return AVERROR_UNKNOWN;
    return timestamp;
}