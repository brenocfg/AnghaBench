#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_13__ {int codec_type; int bit_rate; int /*<<< orphan*/  codec_id; scalar_t__ sample_rate; scalar_t__ channels; } ;
struct TYPE_12__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_11__ {unsigned int* stream_index; int nb_stream_indexes; } ;
struct TYPE_10__ {int disposition; int codec_info_nb_frames; TYPE_4__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVProgram ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR_DECODER_NOT_FOUND ; 
 int AVERROR_STREAM_NOT_FOUND ; 
 int AVMEDIA_TYPE_AUDIO ; 
 int AV_DISPOSITION_DEFAULT ; 
 int AV_DISPOSITION_HEARING_IMPAIRED ; 
 int AV_DISPOSITION_VISUAL_IMPAIRED ; 
 int FFMIN (int,int) ; 
 TYPE_2__* av_find_program_from_stream (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * find_decoder (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int av_find_best_stream(AVFormatContext *ic, enum AVMediaType type,
                        int wanted_stream_nb, int related_stream,
                        AVCodec **decoder_ret, int flags)
{
    int i, nb_streams = ic->nb_streams;
    int ret = AVERROR_STREAM_NOT_FOUND;
    int best_count = -1, best_multiframe = -1, best_disposition = -1;
    int count, multiframe, disposition;
    int64_t best_bitrate = -1;
    int64_t bitrate;
    unsigned *program = NULL;
    const AVCodec *decoder = NULL, *best_decoder = NULL;

    if (related_stream >= 0 && wanted_stream_nb < 0) {
        AVProgram *p = av_find_program_from_stream(ic, NULL, related_stream);
        if (p) {
            program    = p->stream_index;
            nb_streams = p->nb_stream_indexes;
        }
    }
    for (i = 0; i < nb_streams; i++) {
        int real_stream_index = program ? program[i] : i;
        AVStream *st          = ic->streams[real_stream_index];
        AVCodecParameters *par = st->codecpar;
        if (par->codec_type != type)
            continue;
        if (wanted_stream_nb >= 0 && real_stream_index != wanted_stream_nb)
            continue;
        if (type == AVMEDIA_TYPE_AUDIO && !(par->channels && par->sample_rate))
            continue;
        if (decoder_ret) {
            decoder = find_decoder(ic, st, par->codec_id);
            if (!decoder) {
                if (ret < 0)
                    ret = AVERROR_DECODER_NOT_FOUND;
                continue;
            }
        }
        disposition = !(st->disposition & (AV_DISPOSITION_HEARING_IMPAIRED | AV_DISPOSITION_VISUAL_IMPAIRED))
                      + !! (st->disposition & AV_DISPOSITION_DEFAULT);
        count = st->codec_info_nb_frames;
        bitrate = par->bit_rate;
        multiframe = FFMIN(5, count);
        if ((best_disposition >  disposition) ||
            (best_disposition == disposition && best_multiframe >  multiframe) ||
            (best_disposition == disposition && best_multiframe == multiframe && best_bitrate >  bitrate) ||
            (best_disposition == disposition && best_multiframe == multiframe && best_bitrate == bitrate && best_count >= count))
            continue;
        best_disposition = disposition;
        best_count   = count;
        best_bitrate = bitrate;
        best_multiframe = multiframe;
        ret          = real_stream_index;
        best_decoder = decoder;
        if (program && i == nb_streams - 1 && ret < 0) {
            program    = NULL;
            nb_streams = ic->nb_streams;
            /* no related stream found, try again with everything */
            i = 0;
        }
    }
    if (decoder_ret)
        *decoder_ret = (AVCodec*)best_decoder;
    return ret;
}