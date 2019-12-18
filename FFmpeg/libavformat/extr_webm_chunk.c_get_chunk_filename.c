#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ chunk_index; int /*<<< orphan*/  header_filename; TYPE_2__* avf; } ;
typedef  TYPE_1__ WebMChunkContext ;
struct TYPE_6__ {int /*<<< orphan*/  url; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int MAX_FILENAME_SIZE ; 
 scalar_t__ av_get_frame_filename (char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_chunk_filename(AVFormatContext *s, int is_header, char filename[MAX_FILENAME_SIZE])
{
    WebMChunkContext *wc = s->priv_data;
    AVFormatContext *oc = wc->avf;
    if (!filename) {
        return AVERROR(EINVAL);
    }
    if (is_header) {
        int len;
        if (!wc->header_filename) {
            av_log(oc, AV_LOG_ERROR, "No header filename provided\n");
            return AVERROR(EINVAL);
        }
        len = av_strlcpy(filename, wc->header_filename, MAX_FILENAME_SIZE);
        if (len >= MAX_FILENAME_SIZE) {
            av_log(oc, AV_LOG_ERROR, "Header filename too long\n");
            return AVERROR(EINVAL);
        }
    } else {
        if (av_get_frame_filename(filename, MAX_FILENAME_SIZE,
                                  s->url, wc->chunk_index - 1) < 0) {
            av_log(oc, AV_LOG_ERROR, "Invalid chunk filename template '%s'\n", s->url);
            return AVERROR(EINVAL);
        }
    }
    return 0;
}