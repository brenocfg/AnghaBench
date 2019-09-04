#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int nb_side_data; TYPE_4__* side_data; int /*<<< orphan*/  codecpar; int /*<<< orphan*/  metadata; int /*<<< orphan*/  r_frame_rate; int /*<<< orphan*/  avg_frame_rate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  disposition; int /*<<< orphan*/  nb_frames; int /*<<< orphan*/  time_base; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVPacketSideData ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 TYPE_4__* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/ * av_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int avcodec_parameters_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_stream_encode_params_copy(AVStream *dst, const AVStream *src)
{
    int ret, i;

    dst->id                  = src->id;
    dst->time_base           = src->time_base;
    dst->nb_frames           = src->nb_frames;
    dst->disposition         = src->disposition;
    dst->sample_aspect_ratio = src->sample_aspect_ratio;
    dst->avg_frame_rate      = src->avg_frame_rate;
    dst->r_frame_rate        = src->r_frame_rate;

    av_dict_free(&dst->metadata);
    ret = av_dict_copy(&dst->metadata, src->metadata, 0);
    if (ret < 0)
        return ret;

    ret = avcodec_parameters_copy(dst->codecpar, src->codecpar);
    if (ret < 0)
        return ret;

    /* Free existing side data*/
    for (i = 0; i < dst->nb_side_data; i++)
        av_free(dst->side_data[i].data);
    av_freep(&dst->side_data);
    dst->nb_side_data = 0;

    /* Copy side data if present */
    if (src->nb_side_data) {
        dst->side_data = av_mallocz_array(src->nb_side_data,
                                          sizeof(AVPacketSideData));
        if (!dst->side_data)
            return AVERROR(ENOMEM);
        dst->nb_side_data = src->nb_side_data;

        for (i = 0; i < src->nb_side_data; i++) {
            uint8_t *data = av_memdup(src->side_data[i].data,
                                      src->side_data[i].size);
            if (!data)
                return AVERROR(ENOMEM);
            dst->side_data[i].type = src->side_data[i].type;
            dst->side_data[i].size = src->side_data[i].size;
            dst->side_data[i].data = data;
        }
    }

#if FF_API_LAVF_FFSERVER
FF_DISABLE_DEPRECATION_WARNINGS
    av_freep(&dst->recommended_encoder_configuration);
    if (src->recommended_encoder_configuration) {
        const char *conf_str = src->recommended_encoder_configuration;
        dst->recommended_encoder_configuration = av_strdup(conf_str);
        if (!dst->recommended_encoder_configuration)
            return AVERROR(ENOMEM);
    }
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    return 0;
}