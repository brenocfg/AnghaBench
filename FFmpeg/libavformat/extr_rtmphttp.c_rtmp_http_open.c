#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  headers ;
struct TYPE_8__ {scalar_t__ protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_10__ {scalar_t__ protocol_whitelist; int /*<<< orphan*/  priv_data; } ;
struct TYPE_9__ {scalar_t__ port; char* client_id; int initialized; TYPE_5__* stream; int /*<<< orphan*/  host; scalar_t__ tls; } ;
typedef  TYPE_2__ RTMP_HTTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ RTMPTS_DEFAULT_PORT ; 
 scalar_t__ RTMPT_DEFAULT_PORT ; 
 scalar_t__ av_isspace (char) ; 
 int /*<<< orphan*/  av_opt_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set_bin (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_strdup (scalar_t__) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int ffurl_alloc (TYPE_5__**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ffurl_connect (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ffurl_read (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  rtmp_http_close (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

__attribute__((used)) static int rtmp_http_open(URLContext *h, const char *uri, int flags)
{
    RTMP_HTTPContext *rt = h->priv_data;
    char headers[1024], url[1024];
    int ret, off = 0;

    av_url_split(NULL, 0, NULL, 0, rt->host, sizeof(rt->host), &rt->port,
                 NULL, 0, uri);

    /* This is the first request that is sent to the server in order to
     * register a client on the server and start a new session. The server
     * replies with a unique id (usually a number) that is used by the client
     * for all future requests.
     * Note: the reply doesn't contain a value for the polling interval.
     * A successful connect resets the consecutive index that is used
     * in the URLs. */
    if (rt->tls) {
        if (rt->port < 0)
            rt->port = RTMPTS_DEFAULT_PORT;
        ff_url_join(url, sizeof(url), "https", NULL, rt->host, rt->port, "/open/1");
    } else {
        if (rt->port < 0)
            rt->port = RTMPT_DEFAULT_PORT;
        ff_url_join(url, sizeof(url), "http", NULL, rt->host, rt->port, "/open/1");
    }

    /* alloc the http context */
    if ((ret = ffurl_alloc(&rt->stream, url, AVIO_FLAG_READ_WRITE, &h->interrupt_callback)) < 0)
        goto fail;

    /* set options */
    snprintf(headers, sizeof(headers),
             "Cache-Control: no-cache\r\n"
             "Content-type: application/x-fcs\r\n"
             "User-Agent: Shockwave Flash\r\n");
    av_opt_set(rt->stream->priv_data, "headers", headers, 0);
    av_opt_set(rt->stream->priv_data, "multiple_requests", "1", 0);
    av_opt_set_bin(rt->stream->priv_data, "post_data", "", 1, 0);

    if (!rt->stream->protocol_whitelist && h->protocol_whitelist) {
        rt->stream->protocol_whitelist = av_strdup(h->protocol_whitelist);
        if (!rt->stream->protocol_whitelist) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }

    /* open the http context */
    if ((ret = ffurl_connect(rt->stream, NULL)) < 0)
        goto fail;

    /* read the server reply which contains a unique ID */
    for (;;) {
        ret = ffurl_read(rt->stream, rt->client_id + off, sizeof(rt->client_id) - off);
        if (!ret || ret == AVERROR_EOF)
            break;
        if (ret < 0)
            goto fail;
        off += ret;
        if (off == sizeof(rt->client_id)) {
            ret = AVERROR(EIO);
            goto fail;
        }
    }
    while (off > 0 && av_isspace(rt->client_id[off - 1]))
        off--;
    rt->client_id[off] = '\0';

    /* http context is now initialized */
    rt->initialized = 1;
    return 0;

fail:
    rtmp_http_close(h);
    return ret;
}