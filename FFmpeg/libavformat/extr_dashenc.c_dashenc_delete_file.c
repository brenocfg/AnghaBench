#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_6__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  DASHContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_ERROR_MAX_STRING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int avpriv_io_delete (char*) ; 
 scalar_t__ dashenc_io_open (TYPE_1__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int ff_is_http_proto (char*) ; 
 int /*<<< orphan*/  set_http_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dashenc_delete_file(AVFormatContext *s, char *filename) {
    DASHContext *c = s->priv_data;
    int http_base_proto = ff_is_http_proto(filename);

    if (http_base_proto) {
        AVIOContext *out = NULL;
        AVDictionary *http_opts = NULL;

        set_http_options(&http_opts, c);
        av_dict_set(&http_opts, "method", "DELETE", 0);

        if (dashenc_io_open(s, &out, filename, &http_opts) < 0) {
            av_log(s, AV_LOG_ERROR, "failed to delete %s\n", filename);
        }

        av_dict_free(&http_opts);
        ff_format_io_close(s, &out);
    } else {
        int res = avpriv_io_delete(filename);
        if (res < 0) {
            char errbuf[AV_ERROR_MAX_STRING_SIZE];
            av_strerror(res, errbuf, sizeof(errbuf));
            av_log(s, (res == AVERROR(ENOENT) ? AV_LOG_WARNING : AV_LOG_ERROR), "failed to delete %s: %s\n", filename, errbuf);
        }
    }
}