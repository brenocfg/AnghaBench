#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int dummy; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {TYPE_5__* avf; int /*<<< orphan*/  current_segment_final_filename_fmt; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_9__ {int /*<<< orphan*/  url; } ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  HLSSegment ;
typedef  TYPE_2__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 double HLS_MICROSECOND_UNIT ; 
 int HLS_SECOND_LEVEL_SEGMENT_DURATION ; 
 int HLS_SECOND_LEVEL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_format_set_url (TYPE_5__*,char*) ; 
 int replace_int_data_in_filename (char**,int /*<<< orphan*/ ,char,scalar_t__) ; 
 scalar_t__ round (double) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sls_flags_filename_process(struct AVFormatContext *s, HLSContext *hls,
                                      VariantStream *vs, HLSSegment *en,
                                      double duration, int64_t pos, int64_t size)
{
    if ((hls->flags & (HLS_SECOND_LEVEL_SEGMENT_SIZE | HLS_SECOND_LEVEL_SEGMENT_DURATION)) &&
        strlen(vs->current_segment_final_filename_fmt)) {
        char * new_url = av_strdup(vs->current_segment_final_filename_fmt);
        if (!new_url) {
            return AVERROR(ENOMEM);
        }
        ff_format_set_url(vs->avf, new_url);
        if (hls->flags & HLS_SECOND_LEVEL_SEGMENT_SIZE) {
            char *filename = NULL;
            if (replace_int_data_in_filename(&filename, vs->avf->url, 's', pos + size) < 1) {
                av_log(hls, AV_LOG_ERROR,
                       "Invalid second level segment filename template '%s', "
                       "you can try to remove second_level_segment_size flag\n",
                       vs->avf->url);
                av_freep(&filename);
                return AVERROR(EINVAL);
            }
            ff_format_set_url(vs->avf, filename);
        }
        if (hls->flags & HLS_SECOND_LEVEL_SEGMENT_DURATION) {
            char *filename = NULL;
            if (replace_int_data_in_filename(&filename, vs->avf->url,
                                             't',  (int64_t)round(duration * HLS_MICROSECOND_UNIT)) < 1) {
                av_log(hls, AV_LOG_ERROR,
                       "Invalid second level segment filename template '%s', "
                       "you can try to remove second_level_segment_time flag\n",
                       vs->avf->url);
                av_freep(&filename);
                return AVERROR(EINVAL);
            }
            ff_format_set_url(vs->avf, filename);
        }
    }
    return 0;
}