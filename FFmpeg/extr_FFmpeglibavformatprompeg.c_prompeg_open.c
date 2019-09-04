#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_10__ {int /*<<< orphan*/  max_packet_size; } ;
struct TYPE_9__ {int l; int d; scalar_t__ ttl; int init; TYPE_4__* fec_row_hd; TYPE_4__* fec_col_hd; } ;
typedef  TYPE_2__ PrompegContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_closep (TYPE_4__**) ; 
 scalar_t__ ffurl_open_whitelist (TYPE_4__**,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static int prompeg_open(URLContext *h, const char *uri, int flags) {
    PrompegContext *s = h->priv_data;
    AVDictionary *udp_opts = NULL;
    int rtp_port;
    char hostname[256];
    char buf[1024];

    s->fec_col_hd = NULL;
    s->fec_row_hd = NULL;

    if (s->l * s->d > 100) {
        av_log(h, AV_LOG_ERROR, "L * D must be <= 100\n");
        return AVERROR(EINVAL);
    }

    av_url_split(NULL, 0, NULL, 0, hostname, sizeof (hostname), &rtp_port,
            NULL, 0, uri);

    if (rtp_port < 1 || rtp_port > UINT16_MAX - 4) {
        av_log(h, AV_LOG_ERROR, "Invalid RTP base port %d\n", rtp_port);
        return AVERROR(EINVAL);
    }

    if (s->ttl > 0) {
        snprintf(buf, sizeof (buf), "%d", s->ttl);
        av_dict_set(&udp_opts, "ttl", buf, 0);
    }

    ff_url_join(buf, sizeof (buf), "udp", NULL, hostname, rtp_port + 2, NULL);
    if (ffurl_open_whitelist(&s->fec_col_hd, buf, flags, &h->interrupt_callback,
            &udp_opts, h->protocol_whitelist, h->protocol_blacklist, h) < 0)
        goto fail;
    ff_url_join(buf, sizeof (buf), "udp", NULL, hostname, rtp_port + 4, NULL);
    if (ffurl_open_whitelist(&s->fec_row_hd, buf, flags, &h->interrupt_callback,
            &udp_opts, h->protocol_whitelist, h->protocol_blacklist, h) < 0)
        goto fail;

    h->max_packet_size = s->fec_col_hd->max_packet_size;
    s->init = 1;

    av_dict_free(&udp_opts);
    av_log(h, AV_LOG_INFO, "ProMPEG CoP#3-R2 FEC L=%d D=%d\n", s->l, s->d);
    return 0;

fail:
    ffurl_closep(&s->fec_col_hd);
    ffurl_closep(&s->fec_row_hd);
    av_dict_free(&udp_opts);
    return AVERROR(EIO);
}