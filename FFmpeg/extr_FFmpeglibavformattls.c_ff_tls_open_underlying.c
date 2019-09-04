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
struct addrinfo {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  proxy_host ;
typedef  int /*<<< orphan*/  proxy_auth ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  dest ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int listen; char* underlying_host; int numerichost; int /*<<< orphan*/  tcp; scalar_t__ host; } ;
typedef  TYPE_2__ TLSShared ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 scalar_t__ av_strdup (char*) ; 
 scalar_t__ av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ff_http_match_no_proxy (char*,char*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,char*,char*,int,char*,...) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  set_options (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 char* strchr (char const*,char) ; 

int ff_tls_open_underlying(TLSShared *c, URLContext *parent, const char *uri, AVDictionary **options)
{
    int port;
    const char *p;
    char buf[200], opts[50] = "";
    struct addrinfo hints = { 0 }, *ai = NULL;
    const char *proxy_path;
    int use_proxy;

    set_options(c, uri);

    if (c->listen)
        snprintf(opts, sizeof(opts), "?listen=1");

    av_url_split(NULL, 0, NULL, 0, c->underlying_host, sizeof(c->underlying_host), &port, NULL, 0, uri);

    p = strchr(uri, '?');

    if (!p) {
        p = opts;
    } else {
        if (av_find_info_tag(opts, sizeof(opts), "listen", p))
            c->listen = 1;
    }

    ff_url_join(buf, sizeof(buf), "tcp", NULL, c->underlying_host, port, "%s", p);

    hints.ai_flags = AI_NUMERICHOST;
    if (!getaddrinfo(c->underlying_host, NULL, &hints, &ai)) {
        c->numerichost = 1;
        freeaddrinfo(ai);
    }

    if (!c->host && !(c->host = av_strdup(c->underlying_host)))
        return AVERROR(ENOMEM);

    proxy_path = getenv("http_proxy");
    use_proxy = !ff_http_match_no_proxy(getenv("no_proxy"), c->underlying_host) &&
                proxy_path && av_strstart(proxy_path, "http://", NULL);

    if (use_proxy) {
        char proxy_host[200], proxy_auth[200], dest[200];
        int proxy_port;
        av_url_split(NULL, 0, proxy_auth, sizeof(proxy_auth),
                     proxy_host, sizeof(proxy_host), &proxy_port, NULL, 0,
                     proxy_path);
        ff_url_join(dest, sizeof(dest), NULL, NULL, c->underlying_host, port, NULL);
        ff_url_join(buf, sizeof(buf), "httpproxy", proxy_auth, proxy_host,
                    proxy_port, "/%s", dest);
    }

    return ffurl_open_whitelist(&c->tcp, buf, AVIO_FLAG_READ_WRITE,
                                &parent->interrupt_callback, options,
                                parent->protocol_whitelist, parent->protocol_blacklist, parent);
}