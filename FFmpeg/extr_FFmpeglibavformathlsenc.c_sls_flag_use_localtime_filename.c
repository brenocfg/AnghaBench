#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  current_segment_final_filename_fmt; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_11__ {int /*<<< orphan*/  url; } ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ HLSContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int HLS_SECOND_LEVEL_SEGMENT_DURATION ; 
 int HLS_SECOND_LEVEL_SEGMENT_INDEX ; 
 int HLS_SECOND_LEVEL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_format_set_url (TYPE_3__*,char*) ; 
 int replace_int_data_in_filename (char**,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sls_flag_use_localtime_filename(AVFormatContext *oc, HLSContext *c, VariantStream *vs)
{
    if (c->flags & HLS_SECOND_LEVEL_SEGMENT_INDEX) {
        char *filename = NULL;
        if (replace_int_data_in_filename(&filename,
#if FF_API_HLS_WRAP
            oc->url, 'd', c->wrap ? vs->sequence % c->wrap : vs->sequence) < 1) {
#else
            oc->url, 'd', vs->sequence) < 1) {
#endif
            av_log(c, AV_LOG_ERROR, "Invalid second level segment filename template '%s', "
                    "you can try to remove second_level_segment_index flag\n",
                   oc->url);
            av_free(filename);
            return AVERROR(EINVAL);
        }
        ff_format_set_url(oc, filename);
    }
    if (c->flags & (HLS_SECOND_LEVEL_SEGMENT_SIZE | HLS_SECOND_LEVEL_SEGMENT_DURATION)) {
        av_strlcpy(vs->current_segment_final_filename_fmt, oc->url,
                   sizeof(vs->current_segment_final_filename_fmt));
        if (c->flags & HLS_SECOND_LEVEL_SEGMENT_SIZE) {
            char *filename = NULL;
            if (replace_int_data_in_filename(&filename, oc->url, 's', 0) < 1) {
                av_log(c, AV_LOG_ERROR, "Invalid second level segment filename template '%s', "
                        "you can try to remove second_level_segment_size flag\n",
                       oc->url);
                av_free(filename);
                return AVERROR(EINVAL);
            }
            ff_format_set_url(oc, filename);
        }
        if (c->flags & HLS_SECOND_LEVEL_SEGMENT_DURATION) {
            char *filename = NULL;
            if (replace_int_data_in_filename(&filename, oc->url, 't', 0) < 1) {
                av_log(c, AV_LOG_ERROR, "Invalid second level segment filename template '%s', "
                        "you can try to remove second_level_segment_time flag\n",
                       oc->url);
                av_free(filename);
                return AVERROR(EINVAL);
            }
            ff_format_set_url(oc, filename);
        }
    }
    return 0;
}