#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* writer; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_25__ {TYPE_19__* fmt_ctx; int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {int /*<<< orphan*/  discard; } ;
struct TYPE_22__ {int flags; } ;
struct TYPE_21__ {int nb_streams; TYPE_20__** streams; } ;
typedef  TYPE_3__ InputFile ;

/* Variables and functions */
 int /*<<< orphan*/  AVDISCARD_ALL ; 
 int /*<<< orphan*/  CHECK_END ; 
 int /*<<< orphan*/  REALLOCZ_ARRAY_STREAM (int*,int /*<<< orphan*/ ,int) ; 
 int SECTION_ID_FRAMES ; 
 int SECTION_ID_PACKETS ; 
 int SECTION_ID_PACKETS_AND_FRAMES ; 
 int WRITER_FLAG_PUT_PACKETS_AND_FRAMES_IN_SAME_CHAPTER ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int avformat_match_stream_specifier (TYPE_19__*,TYPE_20__*,scalar_t__) ; 
 int /*<<< orphan*/  close_input_file (TYPE_3__*) ; 
 scalar_t__ do_count_frames ; 
 scalar_t__ do_count_packets ; 
 int do_read_frames ; 
 int do_read_packets ; 
 scalar_t__ do_show_chapters ; 
 scalar_t__ do_show_format ; 
 scalar_t__ do_show_frames ; 
 scalar_t__ do_show_packets ; 
 scalar_t__ do_show_programs ; 
 scalar_t__ do_show_streams ; 
 int nb_streams ; 
 int* nb_streams_frames ; 
 int* nb_streams_packets ; 
 int open_input_file (TYPE_3__*,char const*) ; 
 int read_packets (TYPE_2__*,TYPE_3__*) ; 
 int* selected_streams ; 
 int show_chapters (TYPE_2__*,TYPE_3__*) ; 
 int show_format (TYPE_2__*,TYPE_3__*) ; 
 int show_programs (TYPE_2__*,TYPE_3__*) ; 
 int show_streams (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ stream_specifier ; 
 int /*<<< orphan*/  writer_print_section_footer (TYPE_2__*) ; 
 int /*<<< orphan*/  writer_print_section_header (TYPE_2__*,int) ; 

__attribute__((used)) static int probe_file(WriterContext *wctx, const char *filename)
{
    InputFile ifile = { 0 };
    int ret, i;
    int section_id;

    do_read_frames = do_show_frames || do_count_frames;
    do_read_packets = do_show_packets || do_count_packets;

    ret = open_input_file(&ifile, filename);
    if (ret < 0)
        goto end;

#define CHECK_END if (ret < 0) goto end

    nb_streams = ifile.fmt_ctx->nb_streams;
    REALLOCZ_ARRAY_STREAM(nb_streams_frames,0,ifile.fmt_ctx->nb_streams);
    REALLOCZ_ARRAY_STREAM(nb_streams_packets,0,ifile.fmt_ctx->nb_streams);
    REALLOCZ_ARRAY_STREAM(selected_streams,0,ifile.fmt_ctx->nb_streams);

    for (i = 0; i < ifile.fmt_ctx->nb_streams; i++) {
        if (stream_specifier) {
            ret = avformat_match_stream_specifier(ifile.fmt_ctx,
                                                  ifile.fmt_ctx->streams[i],
                                                  stream_specifier);
            CHECK_END;
            else
                selected_streams[i] = ret;
            ret = 0;
        } else {
            selected_streams[i] = 1;
        }
        if (!selected_streams[i])
            ifile.fmt_ctx->streams[i]->discard = AVDISCARD_ALL;
    }

    if (do_read_frames || do_read_packets) {
        if (do_show_frames && do_show_packets &&
            wctx->writer->flags & WRITER_FLAG_PUT_PACKETS_AND_FRAMES_IN_SAME_CHAPTER)
            section_id = SECTION_ID_PACKETS_AND_FRAMES;
        else if (do_show_packets && !do_show_frames)
            section_id = SECTION_ID_PACKETS;
        else // (!do_show_packets && do_show_frames)
            section_id = SECTION_ID_FRAMES;
        if (do_show_frames || do_show_packets)
            writer_print_section_header(wctx, section_id);
        ret = read_packets(wctx, &ifile);
        if (do_show_frames || do_show_packets)
            writer_print_section_footer(wctx);
        CHECK_END;
    }

    if (do_show_programs) {
        ret = show_programs(wctx, &ifile);
        CHECK_END;
    }

    if (do_show_streams) {
        ret = show_streams(wctx, &ifile);
        CHECK_END;
    }
    if (do_show_chapters) {
        ret = show_chapters(wctx, &ifile);
        CHECK_END;
    }
    if (do_show_format) {
        ret = show_format(wctx, &ifile);
        CHECK_END;
    }

end:
    if (ifile.fmt_ctx)
        close_input_file(&ifile);
    av_freep(&nb_streams_frames);
    av_freep(&nb_streams_packets);
    av_freep(&selected_streams);

    return ret;
}