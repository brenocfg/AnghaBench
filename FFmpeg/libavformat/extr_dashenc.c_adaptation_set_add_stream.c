#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__** streams; TYPE_4__* priv_data; } ;
struct TYPE_13__ {scalar_t__ media_type; } ;
struct TYPE_12__ {TYPE_3__* streams; TYPE_5__* as; } ;
struct TYPE_11__ {int as_idx; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ OutputStream ;
typedef  TYPE_4__ DASHContext ;
typedef  TYPE_5__ AdaptationSet ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int adaptation_set_add_stream(AVFormatContext *s, int as_idx, int i)
{
    DASHContext *c = s->priv_data;
    AdaptationSet *as = &c->as[as_idx - 1];
    OutputStream *os = &c->streams[i];

    if (as->media_type != s->streams[i]->codecpar->codec_type) {
        av_log(s, AV_LOG_ERROR, "Codec type of stream %d doesn't match AdaptationSet's media type\n", i);
        return AVERROR(EINVAL);
    } else if (os->as_idx) {
        av_log(s, AV_LOG_ERROR, "Stream %d is already assigned to an AdaptationSet\n", i);
        return AVERROR(EINVAL);
    }
    os->as_idx = as_idx;

    return 0;
}