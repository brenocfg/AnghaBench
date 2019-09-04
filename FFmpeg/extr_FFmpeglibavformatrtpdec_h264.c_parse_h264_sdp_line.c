#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__** streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  codecpar; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  ff_h264_parse_framesize (int /*<<< orphan*/ ,char const*) ; 
 int ff_parse_fmtp (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_parse_fmtp_config_h264 ; 

__attribute__((used)) static int parse_h264_sdp_line(AVFormatContext *s, int st_index,
                               PayloadContext *h264_data, const char *line)
{
    AVStream *stream;
    const char *p = line;

    if (st_index < 0)
        return 0;

    stream = s->streams[st_index];

    if (av_strstart(p, "framesize:", &p)) {
        ff_h264_parse_framesize(stream->codecpar, p);
    } else if (av_strstart(p, "fmtp:", &p)) {
        return ff_parse_fmtp(s, stream, h264_data, p, sdp_parse_fmtp_config_h264);
    } else if (av_strstart(p, "cliprect:", &p)) {
        // could use this if we wanted.
    }

    return 0;
}