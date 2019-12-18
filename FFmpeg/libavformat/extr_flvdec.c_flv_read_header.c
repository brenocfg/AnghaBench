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
struct TYPE_8__ {scalar_t__ start_time; int /*<<< orphan*/  pb; int /*<<< orphan*/  ctx_flags; TYPE_1__* iformat; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int missing_streams; int last_keyframe_stream_index; scalar_t__ sum_flv_tag_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ FLVContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FLV_HEADER_FLAG_HASAUDIO ; 
 int FLV_HEADER_FLAG_HASVIDEO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int avio_r8 (int /*<<< orphan*/ ) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int flv_read_header(AVFormatContext *s)
{
    int flags;
    FLVContext *flv = s->priv_data;
    int offset;
    int pre_tag_size = 0;

    /* Actual FLV data at 0xe40000 in KUX file */
    if(!strcmp(s->iformat->name, "kux"))
        avio_skip(s->pb, 0xe40000);

    avio_skip(s->pb, 4);
    flags = avio_r8(s->pb);

    flv->missing_streams = flags & (FLV_HEADER_FLAG_HASVIDEO | FLV_HEADER_FLAG_HASAUDIO);

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    offset = avio_rb32(s->pb);
    avio_seek(s->pb, offset, SEEK_SET);

    /* Annex E. The FLV File Format
     * E.3 TheFLVFileBody
     *     Field               Type    Comment
     *     PreviousTagSize0    UI32    Always 0
     * */
    pre_tag_size = avio_rb32(s->pb);
    if (pre_tag_size) {
        av_log(s, AV_LOG_WARNING, "Read FLV header error, input file is not a standard flv format, first PreviousTagSize0 always is 0\n");
    }

    s->start_time = 0;
    flv->sum_flv_tag_size = 0;
    flv->last_keyframe_stream_index = -1;

    return 0;
}