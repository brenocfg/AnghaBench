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
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_6__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int /*<<< orphan*/  stream; scalar_t__ tunneling; } ;
typedef  TYPE_2__ RTMPEContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rtmpe_close (TYPE_1__*) ; 

__attribute__((used)) static int rtmpe_open(URLContext *h, const char *uri, int flags)
{
    RTMPEContext *rt = h->priv_data;
    char host[256], url[1024];
    int ret, port;

    av_url_split(NULL, 0, NULL, 0, host, sizeof(host), &port, NULL, 0, uri);

    if (rt->tunneling) {
        if (port < 0)
            port = 80;
        ff_url_join(url, sizeof(url), "ffrtmphttp", NULL, host, port, NULL);
    } else {
        if (port < 0)
            port = 1935;
        ff_url_join(url, sizeof(url), "tcp", NULL, host, port, NULL);
    }

    /* open the tcp or ffrtmphttp connection */
    if ((ret = ffurl_open_whitelist(&rt->stream, url, AVIO_FLAG_READ_WRITE,
                                    &h->interrupt_callback, NULL,
                                    h->protocol_whitelist, h->protocol_blacklist, h)) < 0) {
        rtmpe_close(h);
        return ret;
    }

    return 0;
}