#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {scalar_t__ end; scalar_t__ start; scalar_t__ pos; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ SubfileContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  ffurl_close (int /*<<< orphan*/ ) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int slave_seek (TYPE_1__*) ; 

__attribute__((used)) static int subfile_open(URLContext *h, const char *filename, int flags,
                        AVDictionary **options)
{
    SubfileContext *c = h->priv_data;
    int ret;

    if (!c->end)
        c->end = INT64_MAX;

    if (c->end <= c->start) {
        av_log(h, AV_LOG_ERROR, "end before start\n");
        return AVERROR(EINVAL);
    }
    av_strstart(filename, "subfile:", &filename);
    ret = ffurl_open_whitelist(&c->h, filename, flags, &h->interrupt_callback,
                               options, h->protocol_whitelist, h->protocol_blacklist, h);
    if (ret < 0)
        return ret;
    c->pos = c->start;
    if ((ret = slave_seek(h)) < 0) {
        ffurl_close(c->h);
        return ret;
    }
    return 0;
}