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
struct TYPE_5__ {TYPE_1__* codecpar; } ;
struct TYPE_4__ {scalar_t__ height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strlen (char*) ; 

void ff_hls_write_stream_info(AVStream *st, AVIOContext *out,
                              int bandwidth, const char *filename, char *agroup,
                              char *codecs, char *ccgroup) {

    if (!out || !filename)
        return;

    if (!bandwidth) {
        av_log(NULL, AV_LOG_WARNING,
                "Bandwidth info not available, set audio and video bitrates\n");
        return;
    }

    avio_printf(out, "#EXT-X-STREAM-INF:BANDWIDTH=%d", bandwidth);
    if (st && st->codecpar->width > 0 && st->codecpar->height > 0)
        avio_printf(out, ",RESOLUTION=%dx%d", st->codecpar->width,
                st->codecpar->height);
    if (codecs && strlen(codecs) > 0)
        avio_printf(out, ",CODECS=\"%s\"", codecs);
    if (agroup && strlen(agroup) > 0)
        avio_printf(out, ",AUDIO=\"group_%s\"", agroup);
    if (ccgroup && strlen(ccgroup) > 0)
        avio_printf(out, ",CLOSED-CAPTIONS=\"%s\"", ccgroup);
    avio_printf(out, "\n%s\n\n", filename);
}