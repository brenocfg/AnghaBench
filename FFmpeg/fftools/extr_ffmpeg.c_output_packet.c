#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nb_bitstream_filters; int /*<<< orphan*/  index; int /*<<< orphan*/  file_index; int /*<<< orphan*/ * bsf_ctx; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  OutputFile ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_bsf_receive_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_bsf_send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exit_on_error ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  write_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void output_packet(OutputFile *of, AVPacket *pkt,
                          OutputStream *ost, int eof)
{
    int ret = 0;

    /* apply the output bitstream filters, if any */
    if (ost->nb_bitstream_filters) {
        int idx;

        ret = av_bsf_send_packet(ost->bsf_ctx[0], eof ? NULL : pkt);
        if (ret < 0)
            goto finish;

        eof = 0;
        idx = 1;
        while (idx) {
            /* get a packet from the previous filter up the chain */
            ret = av_bsf_receive_packet(ost->bsf_ctx[idx - 1], pkt);
            if (ret == AVERROR(EAGAIN)) {
                ret = 0;
                idx--;
                continue;
            } else if (ret == AVERROR_EOF) {
                eof = 1;
            } else if (ret < 0)
                goto finish;

            /* send it to the next filter down the chain or to the muxer */
            if (idx < ost->nb_bitstream_filters) {
                ret = av_bsf_send_packet(ost->bsf_ctx[idx], eof ? NULL : pkt);
                if (ret < 0)
                    goto finish;
                idx++;
                eof = 0;
            } else if (eof)
                goto finish;
            else
                write_packet(of, pkt, ost, 0);
        }
    } else if (!eof)
        write_packet(of, pkt, ost, 0);

finish:
    if (ret < 0 && ret != AVERROR_EOF) {
        av_log(NULL, AV_LOG_ERROR, "Error applying bitstream filters to an output "
               "packet for stream #%d:%d.\n", ost->file_index, ost->index);
        if(exit_on_error)
            exit_program(1);
    }
}