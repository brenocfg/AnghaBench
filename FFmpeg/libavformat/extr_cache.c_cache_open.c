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
struct TYPE_8__ {scalar_t__ fd; char* filename; int /*<<< orphan*/  inner; } ;
typedef  TYPE_2__ Context ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 scalar_t__ avpriv_tempfile (char*,char**,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int unlink (char*) ; 

__attribute__((used)) static int cache_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    int ret;
    char *buffername;
    Context *c= h->priv_data;

    av_strstart(arg, "cache:", &arg);

    c->fd = avpriv_tempfile("ffcache", &buffername, 0, h);
    if (c->fd < 0){
        av_log(h, AV_LOG_ERROR, "Failed to create tempfile\n");
        return c->fd;
    }

    ret = unlink(buffername);

    if (ret >= 0)
        av_freep(&buffername);
    else
        c->filename = buffername;

    return ffurl_open_whitelist(&c->inner, arg, flags, &h->interrupt_callback,
                                options, h->protocol_whitelist, h->protocol_blacklist, h);
}