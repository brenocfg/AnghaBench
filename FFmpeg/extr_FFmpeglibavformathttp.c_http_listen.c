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
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  lower_url ;
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_6__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {scalar_t__ listen; int reply_code; int /*<<< orphan*/  chained_options; int /*<<< orphan*/  handshake_step; int /*<<< orphan*/  hd; } ;
typedef  TYPE_2__ HTTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 scalar_t__ HTTP_SINGLE ; 
 int /*<<< orphan*/  LOWER_PROTO ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int av_dict_set_int (int /*<<< orphan*/ **,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_url_split (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char const*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int http_handshake (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int http_listen(URLContext *h, const char *uri, int flags,
                       AVDictionary **options) {
    HTTPContext *s = h->priv_data;
    int ret;
    char hostname[1024], proto[10];
    char lower_url[100];
    const char *lower_proto = "tcp";
    int port;
    av_url_split(proto, sizeof(proto), NULL, 0, hostname, sizeof(hostname), &port,
                 NULL, 0, uri);
    if (!strcmp(proto, "https"))
        lower_proto = "tls";
    ff_url_join(lower_url, sizeof(lower_url), lower_proto, NULL, hostname, port,
                NULL);
    if ((ret = av_dict_set_int(options, "listen", s->listen, 0)) < 0)
        goto fail;
    if ((ret = ffurl_open_whitelist(&s->hd, lower_url, AVIO_FLAG_READ_WRITE,
                                    &h->interrupt_callback, options,
                                    h->protocol_whitelist, h->protocol_blacklist, h
                                   )) < 0)
        goto fail;
    s->handshake_step = LOWER_PROTO;
    if (s->listen == HTTP_SINGLE) { /* single client */
        s->reply_code = 200;
        while ((ret = http_handshake(h)) > 0);
    }
fail:
    av_dict_free(&s->chained_options);
    return ret;
}