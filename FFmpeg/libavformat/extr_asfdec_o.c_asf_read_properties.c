#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int b_flags; int nb_packets; int duration; int preroll; void* packet_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  GUIDParseTable ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int ASF_FLAG_BROADCAST ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int avio_rl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 struct tm* gmtime_r (int*,struct tm*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int asf_read_properties(AVFormatContext *s, const GUIDParseTable *g)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    time_t creation_time;

    avio_rl64(pb); // read object size
    avio_skip(pb, 16); // skip File ID
    avio_skip(pb, 8);  // skip File size
    creation_time = avio_rl64(pb);
    if (!(asf->b_flags & ASF_FLAG_BROADCAST)) {
        struct tm tmbuf;
        struct tm *tm;
        char buf[64];

        // creation date is in 100 ns units from 1 Jan 1601, conversion to s
        creation_time /= 10000000;
        // there are 11644473600 seconds between 1 Jan 1601 and 1 Jan 1970
        creation_time -= 11644473600;
        tm = gmtime_r(&creation_time, &tmbuf);
        if (tm) {
            if (!strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm))
                buf[0] = '\0';
        } else
            buf[0] = '\0';
        if (buf[0]) {
            if (av_dict_set(&s->metadata, "creation_time", buf, 0) < 0)
                av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
        }
    }
    asf->nb_packets  = avio_rl64(pb);
    asf->duration    = avio_rl64(pb) / 10000; // stream duration
    avio_skip(pb, 8); // skip send duration
    asf->preroll     = avio_rl64(pb);
    asf->duration   -= asf->preroll;
    asf->b_flags     = avio_rl32(pb);
    avio_skip(pb, 4); // skip minimal packet size
    asf->packet_size  = avio_rl32(pb);
    avio_skip(pb, 4); // skip max_bitrate

    return 0;
}