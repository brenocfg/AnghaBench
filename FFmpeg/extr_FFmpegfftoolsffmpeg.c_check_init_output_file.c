#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_13__ {int nb_streams; int /*<<< orphan*/  url; int /*<<< orphan*/  interrupt_callback; } ;
struct TYPE_12__ {int ost_index; int header_written; TYPE_8__* ctx; int /*<<< orphan*/  opts; } ;
struct TYPE_11__ {int /*<<< orphan*/  muxing_queue; TYPE_1__* st; int /*<<< orphan*/  mux_timebase; int /*<<< orphan*/  initialized; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ OutputFile ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dump_format (TYPE_8__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int avformat_write_header (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_cb ; 
 TYPE_2__** output_streams ; 
 int /*<<< orphan*/  print_sdp () ; 
 scalar_t__ sdp_filename ; 
 scalar_t__ want_sdp ; 
 int /*<<< orphan*/  write_packet (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static int check_init_output_file(OutputFile *of, int file_index)
{
    int ret, i;

    for (i = 0; i < of->ctx->nb_streams; i++) {
        OutputStream *ost = output_streams[of->ost_index + i];
        if (!ost->initialized)
            return 0;
    }

    of->ctx->interrupt_callback = int_cb;

    ret = avformat_write_header(of->ctx, &of->opts);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR,
               "Could not write header for output file #%d "
               "(incorrect codec parameters ?): %s\n",
               file_index, av_err2str(ret));
        return ret;
    }
    //assert_avoptions(of->opts);
    of->header_written = 1;

    av_dump_format(of->ctx, file_index, of->ctx->url, 1);

    if (sdp_filename || want_sdp)
        print_sdp();

    /* flush the muxing queues */
    for (i = 0; i < of->ctx->nb_streams; i++) {
        OutputStream *ost = output_streams[of->ost_index + i];

        /* try to improve muxing time_base (only possible if nothing has been written yet) */
        if (!av_fifo_size(ost->muxing_queue))
            ost->mux_timebase = ost->st->time_base;

        while (av_fifo_size(ost->muxing_queue)) {
            AVPacket pkt;
            av_fifo_generic_read(ost->muxing_queue, &pkt, sizeof(pkt), NULL);
            write_packet(of, &pkt, ost, 1);
        }
    }

    return 0;
}