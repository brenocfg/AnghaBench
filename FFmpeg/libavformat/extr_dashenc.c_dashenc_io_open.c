#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_7__ {int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  http_persistent; } ;
typedef  TYPE_1__ DASHContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_MUXER_NOT_FOUND ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int ff_http_do_new_request (int /*<<< orphan*/ *,char*) ; 
 int ff_is_http_proto (char*) ; 
 int /*<<< orphan*/ * ffio_geturlcontext (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int dashenc_io_open(AVFormatContext *s, AVIOContext **pb, char *filename,
                           AVDictionary **options) {
    DASHContext *c = s->priv_data;
    int http_base_proto = filename ? ff_is_http_proto(filename) : 0;
    int err = AVERROR_MUXER_NOT_FOUND;
    if (!*pb || !http_base_proto || !c->http_persistent) {
        err = s->io_open(s, pb, filename, AVIO_FLAG_WRITE, options);
#if CONFIG_HTTP_PROTOCOL
    } else {
        URLContext *http_url_context = ffio_geturlcontext(*pb);
        av_assert0(http_url_context);
        err = ff_http_do_new_request(http_url_context, filename);
        if (err < 0)
            ff_format_io_close(s, pb);
#endif
    }
    return err;
}