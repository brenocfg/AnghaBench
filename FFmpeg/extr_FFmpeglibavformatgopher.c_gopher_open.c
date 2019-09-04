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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  auth ;
struct TYPE_7__ {int is_streamed; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int /*<<< orphan*/ * hd; } ;
typedef  TYPE_2__ GopherContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int*,char*,int,char const*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gopher_close (TYPE_1__*) ; 
 int gopher_connect (TYPE_1__*,char*) ; 

__attribute__((used)) static int gopher_open(URLContext *h, const char *uri, int flags)
{
    GopherContext *s = h->priv_data;
    char hostname[1024], auth[1024], path[1024], buf[1024];
    int port, err;

    h->is_streamed = 1;

    /* needed in any case to build the host string */
    av_url_split(NULL, 0, auth, sizeof(auth), hostname, sizeof(hostname), &port,
                 path, sizeof(path), uri);

    if (port < 0)
        port = 70;

    ff_url_join(buf, sizeof(buf), "tcp", NULL, hostname, port, NULL);

    s->hd = NULL;
    err = ffurl_open_whitelist(&s->hd, buf, AVIO_FLAG_READ_WRITE,
                               &h->interrupt_callback, NULL, h->protocol_whitelist, h->protocol_blacklist, h);
    if (err < 0)
        goto fail;

    if ((err = gopher_connect(h, path)) < 0)
        goto fail;
    return 0;
 fail:
    gopher_close(h);
    return err;
}