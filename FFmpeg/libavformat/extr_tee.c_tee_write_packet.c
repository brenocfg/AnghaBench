#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {unsigned int nb_slaves; TYPE_1__* slaves; } ;
typedef  TYPE_3__ TeeContext ;
struct TYPE_26__ {int /*<<< orphan*/  time_base_out; } ;
struct TYPE_25__ {TYPE_2__** streams; TYPE_3__* priv_data; } ;
struct TYPE_24__ {unsigned int stream_index; } ;
struct TYPE_22__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_21__ {int* stream_map; TYPE_6__** bsfs; TYPE_5__* avf; } ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_bsf_receive_packet (TYPE_6__*,TYPE_4__*) ; 
 int av_bsf_send_packet (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int av_interleaved_write_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int av_packet_ref (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_packet_rescale_ts (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int tee_process_slave_failure (TYPE_5__*,unsigned int,int) ; 

__attribute__((used)) static int tee_write_packet(AVFormatContext *avf, AVPacket *pkt)
{
    TeeContext *tee = avf->priv_data;
    AVFormatContext *avf2;
    AVBSFContext *bsfs;
    AVPacket pkt2;
    int ret_all = 0, ret;
    unsigned i, s;
    int s2;

    for (i = 0; i < tee->nb_slaves; i++) {
        if (!(avf2 = tee->slaves[i].avf))
            continue;

        /* Flush slave if pkt is NULL*/
        if (!pkt) {
            ret = av_interleaved_write_frame(avf2, NULL);
            if (ret < 0) {
                ret = tee_process_slave_failure(avf, i, ret);
                if (!ret_all && ret < 0)
                    ret_all = ret;
            }
            continue;
        }

        s = pkt->stream_index;
        s2 = tee->slaves[i].stream_map[s];
        if (s2 < 0)
            continue;

        memset(&pkt2, 0, sizeof(AVPacket));
        if ((ret = av_packet_ref(&pkt2, pkt)) < 0)
            if (!ret_all) {
                ret_all = ret;
                continue;
            }
        bsfs = tee->slaves[i].bsfs[s2];
        pkt2.stream_index = s2;

        ret = av_bsf_send_packet(bsfs, &pkt2);
        if (ret < 0) {
            av_log(avf, AV_LOG_ERROR, "Error while sending packet to bitstream filter: %s\n",
                   av_err2str(ret));
            ret = tee_process_slave_failure(avf, i, ret);
            if (!ret_all && ret < 0)
                ret_all = ret;
        }

        while(1) {
            ret = av_bsf_receive_packet(bsfs, &pkt2);
            if (ret == AVERROR(EAGAIN)) {
                ret = 0;
                break;
            } else if (ret < 0) {
                break;
            }

            av_packet_rescale_ts(&pkt2, bsfs->time_base_out,
                                 avf2->streams[s2]->time_base);
            ret = av_interleaved_write_frame(avf2, &pkt2);
            if (ret < 0)
                break;
        };

        if (ret < 0) {
            ret = tee_process_slave_failure(avf, i, ret);
            if (!ret_all && ret < 0)
                ret_all = ret;
        }
    }
    return ret_all;
}