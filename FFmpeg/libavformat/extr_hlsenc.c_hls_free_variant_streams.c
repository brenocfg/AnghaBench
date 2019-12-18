#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct HLSContext {int nb_varstreams; TYPE_1__* var_streams; } ;
struct TYPE_2__ {int /*<<< orphan*/  varname; int /*<<< orphan*/  baseurl; int /*<<< orphan*/  ccgroup; int /*<<< orphan*/  language; int /*<<< orphan*/  agroup; int /*<<< orphan*/  streams; int /*<<< orphan*/  m3u8_name; int /*<<< orphan*/  old_segments; int /*<<< orphan*/  segments; int /*<<< orphan*/  vtt_m3u8_name; int /*<<< orphan*/  vtt_basename; int /*<<< orphan*/  fmp4_init_filename; int /*<<< orphan*/  base_output_dirname; int /*<<< orphan*/  basename; int /*<<< orphan*/ * vtt_avf; } ;
typedef  TYPE_1__ VariantStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hls_free_segments (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hls_free_variant_streams(struct HLSContext *hls)
{
    int i = 0;
    AVFormatContext *vtt_oc = NULL;
    VariantStream *vs = NULL;

    for (i = 0; i < hls->nb_varstreams; i++) {
        vs = &hls->var_streams[i];
        vtt_oc = vs->vtt_avf;

        av_freep(&vs->basename);
        av_freep(&vs->base_output_dirname);
        av_freep(&vs->fmp4_init_filename);
        if (vtt_oc) {
            av_freep(&vs->vtt_basename);
            av_freep(&vs->vtt_m3u8_name);
        }

        hls_free_segments(vs->segments);
        hls_free_segments(vs->old_segments);
        av_freep(&vs->m3u8_name);
        av_freep(&vs->streams);
        av_freep(&vs->agroup);
        av_freep(&vs->language);
        av_freep(&vs->ccgroup);
        av_freep(&vs->baseurl);
        av_freep(&vs->varname);
    }
}