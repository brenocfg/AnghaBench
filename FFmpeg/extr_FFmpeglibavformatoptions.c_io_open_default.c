#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* url; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* oformat; TYPE_1__* iformat; } ;
struct TYPE_7__ {char const* name; } ;
struct TYPE_6__ {char const* name; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVIO_FLAG_WRITE ; 
 int AV_LOG_DEBUG ; 
 int AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int,char*,char const*,char*) ; 
 int ffio_open_whitelist (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int io_open_default(AVFormatContext *s, AVIOContext **pb,
                           const char *url, int flags, AVDictionary **options)
{
    int loglevel;

    if (!strcmp(url, s->url) ||
        s->iformat && !strcmp(s->iformat->name, "image2") ||
        s->oformat && !strcmp(s->oformat->name, "image2")
    ) {
        loglevel = AV_LOG_DEBUG;
    } else
        loglevel = AV_LOG_INFO;

    av_log(s, loglevel, "Opening \'%s\' for %s\n", url, flags & AVIO_FLAG_WRITE ? "writing" : "reading");

#if FF_API_OLD_OPEN_CALLBACKS
FF_DISABLE_DEPRECATION_WARNINGS
    if (s->open_cb)
        return s->open_cb(s, pb, url, flags, &s->interrupt_callback, options);
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    return ffio_open_whitelist(pb, url, flags, &s->interrupt_callback, options, s->protocol_whitelist, s->protocol_blacklist);
}