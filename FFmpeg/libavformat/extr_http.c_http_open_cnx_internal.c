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
typedef  int /*<<< orphan*/  urlbuf ;
typedef  int /*<<< orphan*/  proxyauth ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  path1 ;
typedef  int /*<<< orphan*/  hoststr ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  auth ;
struct TYPE_6__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {char const* location; char* http_proxy; int /*<<< orphan*/  hd; } ;
typedef  TYPE_2__ HTTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int MAX_URL_SIZE ; 
 scalar_t__ av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_url_split (char*,int,char*,int,char*,int,int*,char*,int,char const*) ; 
 int /*<<< orphan*/  ff_http_match_no_proxy (char*,char*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char const*,int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* getenv (char*) ; 
 int http_connect (TYPE_1__*,char const*,char const*,char*,char*,char*,int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int http_open_cnx_internal(URLContext *h, AVDictionary **options)
{
    const char *path, *proxy_path, *lower_proto = "tcp", *local_path;
    char hostname[1024], hoststr[1024], proto[10];
    char auth[1024], proxyauth[1024] = "";
    char path1[MAX_URL_SIZE];
    char buf[1024], urlbuf[MAX_URL_SIZE];
    int port, use_proxy, err, location_changed = 0;
    HTTPContext *s = h->priv_data;

    av_url_split(proto, sizeof(proto), auth, sizeof(auth),
                 hostname, sizeof(hostname), &port,
                 path1, sizeof(path1), s->location);
    ff_url_join(hoststr, sizeof(hoststr), NULL, NULL, hostname, port, NULL);

    proxy_path = s->http_proxy ? s->http_proxy : getenv("http_proxy");
    use_proxy  = !ff_http_match_no_proxy(getenv("no_proxy"), hostname) &&
                 proxy_path && av_strstart(proxy_path, "http://", NULL);

    if (!strcmp(proto, "https")) {
        lower_proto = "tls";
        use_proxy   = 0;
        if (port < 0)
            port = 443;
    }
    if (port < 0)
        port = 80;

    if (path1[0] == '\0')
        path = "/";
    else
        path = path1;
    local_path = path;
    if (use_proxy) {
        /* Reassemble the request URL without auth string - we don't
         * want to leak the auth to the proxy. */
        ff_url_join(urlbuf, sizeof(urlbuf), proto, NULL, hostname, port, "%s",
                    path1);
        path = urlbuf;
        av_url_split(NULL, 0, proxyauth, sizeof(proxyauth),
                     hostname, sizeof(hostname), &port, NULL, 0, proxy_path);
    }

    ff_url_join(buf, sizeof(buf), lower_proto, NULL, hostname, port, NULL);

    if (!s->hd) {
        err = ffurl_open_whitelist(&s->hd, buf, AVIO_FLAG_READ_WRITE,
                                   &h->interrupt_callback, options,
                                   h->protocol_whitelist, h->protocol_blacklist, h);
        if (err < 0)
            return err;
    }

    err = http_connect(h, path, local_path, hoststr,
                       auth, proxyauth, &location_changed);
    if (err < 0)
        return err;

    return location_changed;
}