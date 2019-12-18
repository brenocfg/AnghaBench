#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * streams; } ;
struct TYPE_8__ {int channels; scalar_t__ interleaving; scalar_t__ crc; int /*<<< orphan*/  octet_align; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  amr_parse_fmtp ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_strstart (char const*,char*,char const**) ; 
 int ff_parse_fmtp (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amr_parse_sdp_line(AVFormatContext *s, int st_index,
                              PayloadContext *data, const char *line)
{
    const char *p;
    int ret;

    if (st_index < 0)
        return 0;

    /* Parse an fmtp line this one:
     * a=fmtp:97 octet-align=1; interleaving=0
     * That is, a normal fmtp: line followed by semicolon & space
     * separated key/value pairs.
     */
    if (av_strstart(line, "fmtp:", &p)) {
        ret = ff_parse_fmtp(s, s->streams[st_index], data, p, amr_parse_fmtp);
        if (!data->octet_align || data->crc ||
            data->interleaving || data->channels != 1) {
            av_log(s, AV_LOG_ERROR, "Unsupported RTP/AMR configuration!\n");
            return -1;
        }
        return ret;
    }
    return 0;
}