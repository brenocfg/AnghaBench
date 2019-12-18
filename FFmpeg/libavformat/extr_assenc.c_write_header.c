#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_10__ {TYPE_2__* codecpar; } ;
struct TYPE_9__ {size_t trailer_size; char* trailer; int ssa_mode; } ;
struct TYPE_8__ {scalar_t__ codec_id; size_t extradata_size; char* extradata; } ;
struct TYPE_7__ {int nb_streams; int /*<<< orphan*/  pb; TYPE_5__** streams; TYPE_3__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVCodecParameters ;
typedef  TYPE_3__ ASSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_ASS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_5__*,int,int,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int write_header(AVFormatContext *s)
{
    ASSContext *ass = s->priv_data;
    AVCodecParameters *par = s->streams[0]->codecpar;

    if (s->nb_streams != 1 || par->codec_id != AV_CODEC_ID_ASS) {
        av_log(s, AV_LOG_ERROR, "Exactly one ASS/SSA stream is needed.\n");
        return AVERROR(EINVAL);
    }
    avpriv_set_pts_info(s->streams[0], 64, 1, 100);
    if (par->extradata_size > 0) {
        size_t header_size = par->extradata_size;
        uint8_t *trailer = strstr(par->extradata, "\n[Events]");

        if (trailer)
            trailer = strstr(trailer, "Format:");
        if (trailer)
            trailer = strstr(trailer, "\n");

        if (trailer++) {
            header_size = (trailer - par->extradata);
            ass->trailer_size = par->extradata_size - header_size;
            if (ass->trailer_size)
                ass->trailer = trailer;
        }

        avio_write(s->pb, par->extradata, header_size);
        if (par->extradata[header_size - 1] != '\n')
            avio_write(s->pb, "\r\n", 2);
        ass->ssa_mode = !strstr(par->extradata, "\n[V4+ Styles]");
        if (!strstr(par->extradata, "\n[Events]"))
            avio_printf(s->pb, "[Events]\r\nFormat: %s, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text\r\n",
                        ass->ssa_mode ? "Marked" : "Layer");
    }
    avio_flush(s->pb);

    return 0;
}