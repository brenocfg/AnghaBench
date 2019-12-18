#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ogg_stream {int pflags; int* buf; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_8__ {TYPE_2__** streams; struct ogg* priv_data; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {int codec_id; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
#define  AV_CODEC_ID_THEORA 129 
#define  AV_CODEC_ID_VP8 128 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void ogg_validate_keyframe(AVFormatContext *s, int idx, int pstart, int psize)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    int invalid = 0;
    if (psize) {
        switch (s->streams[idx]->codecpar->codec_id) {
        case AV_CODEC_ID_THEORA:
            invalid = !!(os->pflags & AV_PKT_FLAG_KEY) != !(os->buf[pstart] & 0x40);
        break;
        case AV_CODEC_ID_VP8:
            invalid = !!(os->pflags & AV_PKT_FLAG_KEY) != !(os->buf[pstart] & 1);
        }
        if (invalid) {
            os->pflags ^= AV_PKT_FLAG_KEY;
            av_log(s, AV_LOG_WARNING, "Broken file, %skeyframe not correctly marked.\n",
                   (os->pflags & AV_PKT_FLAG_KEY) ? "" : "non-");
        }
    }
}