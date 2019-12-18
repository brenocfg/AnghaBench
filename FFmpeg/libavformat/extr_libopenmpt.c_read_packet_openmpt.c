#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int size; scalar_t__ data; } ;
struct TYPE_8__ {int channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ OpenMPTContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AUDIO_PKT_SIZE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int av_new_packet (TYPE_2__*,int) ; 
 int openmpt_module_read_float_mono (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 int openmpt_module_read_interleaved_float_quad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 int openmpt_module_read_interleaved_float_stereo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 

__attribute__((used)) static int read_packet_openmpt(AVFormatContext *s, AVPacket *pkt)
{
    OpenMPTContext *openmpt = s->priv_data;
    int n_samples = AUDIO_PKT_SIZE / (openmpt->channels ? openmpt->channels*4 : 4);
    int ret;

    if ((ret = av_new_packet(pkt, AUDIO_PKT_SIZE)) < 0)
        return ret;

    switch (openmpt->channels) {
    case 1:
        ret = openmpt_module_read_float_mono(openmpt->module, openmpt->sample_rate,
                                             n_samples, (float *)pkt->data);
        break;
    case 2:
        ret = openmpt_module_read_interleaved_float_stereo(openmpt->module, openmpt->sample_rate,
                                                           n_samples, (float *)pkt->data);
        break;
    case 4:
        ret = openmpt_module_read_interleaved_float_quad(openmpt->module, openmpt->sample_rate,
                                                         n_samples, (float *)pkt->data);
        break;
    default:
        av_log(s, AV_LOG_ERROR, "Unsupported number of channels: %d", openmpt->channels);
        return AVERROR(EINVAL);
    }

    if (ret < 1) {
        pkt->size = 0;
        return AVERROR_EOF;
    }

    pkt->size = ret * (openmpt->channels * 4);

    return 0;
}