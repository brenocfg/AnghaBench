#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_5__ {scalar_t__ eof_reached; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_PROTOCOL_NOT_FOUND ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int ff_http_do_new_request2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ffio_geturlcontext (TYPE_1__*) ; 

__attribute__((used)) static int open_url_keepalive(AVFormatContext *s, AVIOContext **pb,
                              const char *url, AVDictionary **options)
{
#if !CONFIG_HTTP_PROTOCOL
    return AVERROR_PROTOCOL_NOT_FOUND;
#else
    int ret;
    URLContext *uc = ffio_geturlcontext(*pb);
    av_assert0(uc);
    (*pb)->eof_reached = 0;
    ret = ff_http_do_new_request2(uc, url, options);
    if (ret < 0) {
        ff_format_io_close(s, pb);
    }
    return ret;
#endif
}